/*
 * APP.c
 *
 * Created: 8/13/2024 6:51:38 PM
 *  Author: youefkh05
 */ 

#include "APP.h"

#define fan1_max_speed	(250)

// Global variables
E2PROM_State currentState =Normal_state;
uint8_t buttonPressed = 0;
uint8_t emergency_flag = 0;//j
uint8_t emergency_counter =0;
uint8_t overflow_count=0;
dc_motor DC_fan1=DC_Motor1;

/*	Variables	(local but global to debugg)*/
uint8_t reset=0;
volatile uint8_t bot1_intur=0;
volatile uint8_t temp_counter=0;
volatile temp temperature=0;
uint8_t Speed_Scale=100;

/*		Semaphore		*/
xSemaphoreHandle Bot1_Semaphore;
xSemaphoreHandle Emer_Semaphore;

/*		Tasks		*/
TaskHandle_t xHanleTMP;
TaskHandle_t xHanleUART;
TaskHandle_t xHanleEEState;
TaskHandle_t xHanleFan1;
TaskHandle_t xHanleEmergency;

uint8_t EEPROM_State_Add=0b01000000;	//any place

void App_Init(void){
	/*		Initializations		*/
	DC_Initialize(DC_fan1);
	Initialize_E2PROM_State();
	Initialize_TEMP_SENSOR();
	ADC_Initialize(AVCC,ADC_PRE0);
	LED1_Initialize();
	LED1_OFF();
	
	DIO_SetPinDirection(BOT1_PORT,BOT1_PIN,DIO_INPUT); //push button
	//Timer0_OVF_WithInterrupt_Initialize();
	
	uart_status UART_State= UART_Initialize_WithoutInterrupt(UART_9600,Synchronous, Disable , Bits_8, Bit_1);
	if(UART_State==UART_NOK){
		return ;
	}

	External_Interrupt0_Initalize(INT0_RISING);

	// Read initial state from EEPROM
	uint8_t x= Read_E2PROM_State();
	if (x==0)
	{
		DC_Start(DC_fan1,DC_CW);
	}
	_delay_ms(10);
	
}

void Free_RTOS_Init(void){
	/*		Semaphore		*/
	Bot1_Semaphore=xSemaphoreCreateBinary();
	xSemaphoreTake(Bot1_Semaphore, 0);
	
	Emer_Semaphore=xSemaphoreCreateBinary();
	xSemaphoreTake(Emer_Semaphore, 0);

	/*		Task		*/
	xTaskCreate(&tmp,"TMP_TASK",100,NULL,0,&xHanleTMP);
	xTaskCreate(&uart,"UART_TASK",100,NULL,3,&xHanleUART);
	xTaskCreate(&eestate,"EESTATE_TASK",100,NULL,0,&xHanleEEState);
	xTaskCreate(&fan1,"FAN1_TASK",100,NULL,2,&xHanleFan1);
	xTaskCreate(&emergency,"EMER_TASK",100,NULL,5,&xHanleEmergency);
	
}

void Initialize_E2PROM_State(void){
	
	/* It should have a normal state first	*/
	eeprom_update_byte (&EEPROM_State_Add, (uint8_t)Normal_state);	
	eeprom_update_byte (&EEPROM_State_Add, (uint8_t)Normal_state);	
}

uint8_t Read_E2PROM_State (void){
	
	/*	read the state	*/
	uint8_t x= eeprom_read_byte (&EEPROM_State_Add); 		
	return x;
}

void Write_E2PROM_State( E2PROM_State state){
	
	/*	write the state	*/
	eeprom_write_byte (&EEPROM_State_Add, (uint8_t)state); 
}


void handle_event(temp T,uint8_t *counter,dc_motor DC_fan,uint8_t Speed, E2PROM_State* S,uint8_t* reset){
	
	/*	check the state	*/
	check_State(T,counter,S);
	handle_State(T,DC_fan,Speed,S,reset);
}

void check_State(temp T,uint8_t *counter,E2PROM_State* S){
	
	/*	check if the state is changed	*/
	if(T<50.0 && *S!=Normal_state){
		*counter=0;
		*S=Normal_state;
		eeprom_write_byte (&EEPROM_State_Add, *S);
	}
	else if(T>=50.0 && *S==Normal_state){
		*S=Emergency_state;
		eeprom_write_byte (&EEPROM_State_Add, *S);
	}
	
}

void handle_State(temp T,dc_motor DC_fan,uint8_t Speed,E2PROM_State* S,uint8_t* reset){
	switch (*S){
		case Normal_state:
			if(T<=20.0){
				DC_Stop(DC_fan);
			}
			else if (T>20.0 && T<=40.0){
				//increase fan speed
				DC_Start(DC_fan,DC_CW);
				DC_Change_Speed(DC_fan,((temp)T*5*Speed)/100);
			}
			else if (T>40 &&T<=50) {
				//max speed
				DC_Start(DC_fan,DC_CW);
				DC_Change_Speed(DC_fan,(fan1_max_speed*Speed)/100);
			}
			else{
				//nothing
			}
		break;
		case Emergency_state:
			//max speed
			DC_Start(DC_fan,DC_CW);
			DC_Change_Speed(DC_fan,(fan1_max_speed*Speed)/100);
			
		break;
		case Abnormal_state:
			//max speed
			DC_Start(DC_fan,DC_CW);
			DC_Change_Speed(DC_fan,(fan1_max_speed*Speed)/100);
			*reset=1;
		break;
	}

}

void UART_Transmit_State(const temp T,uint8_t counter,uint8_t *bot1f){
	if (T>=50)
	{	
		if (counter<Emergency_counter_max)
		{	//Emergency
			/* Reset the flag	*/
			*bot1f=0;
			//send the emergency signal
			UART_Transmit_Word(Emergency_Mes);
		} 
		else
		{
			//Abnormal
			UART_Transmit_Word(Abnormal_Mes);
		}

	}
	else if (T>40 && T<=50 && *bot1f==1)
	{	
		//send the off signal
		UART_Transmit_Word(Off_Mes);
	}
	else{
		/* Reset the flag	*/
		*bot1f=0;
		UART_Transmit_Word(T);
	}
}

void UART_Receive_Speed(uint8_t* Speed){
	uint8_t temp_Speed;
	uart_status s	=	UART_Receive_Character(&temp_Speed); 
	if (s==UART_OK)
	{
		*Speed=temp_Speed;
	}
}



/*
void pot(void *par){
	static uint16_t pot_rd=0;
	LCD_voidGoToXY(0,0);
	LCD_voidWriteString((uint8_t *)"POT:");
	while(1){
		if (xSemaphoreTake(LCD_Semaphore, 5000) == pdTRUE)
		{
			LCD_voidGoToXY(0,4);
			LCD_voidWriteString((uint8_t *)"    ");
			pot_rd=ADC_Read(ADC_1);
			LCD_voidGoToXY(0,4);
			LCD_voidWriteNumber(pot_rd);
			xSemaphoreGive(LCD_Semaphore);
			vTaskDelay(200);
		}
		else{
			
		}
		
	}
	
}
*/

void tmp(void *par){
	static uint16_t tmp_rd=0;
	/*
	LCD_voidGoToXY(1,0);
	LCD_voidWriteString((uint8_t*)"TMP:");
	*/
	while(1){
		/*
		if (xSemaphoreTake(LCD_Semaphore, 5000) == pdTRUE)
		{
			LCD_voidGoToXY(1,4);
			LCD_voidWriteString((uint8_t *)"     ");
			tmp_rd=Read_TEMP_SENSOR();
			LCD_voidGoToXY(1,4);
			LCD_voidWriteNumber(tmp_rd);
			LCD_voidWriteString((uint8_t *)"C");
			xSemaphoreGive(LCD_Semaphore);
			vTaskDelay(200);
		}
		else{
			
		}
		*/
		temperature=Read_TEMP_SENSOR();
		if(temperature>=Emergecy_Max_Temp){
			if (0==emergency_flag)	//enter emergency	
			{
				emergency_flag=1;
				xSemaphoreGive(Emer_Semaphore);
			}
			vTaskDelay(pdMS_TO_TICKS(70));
		}
		else{
			if (1==emergency_flag) //exit emergency
			{
				xSemaphoreGive(Emer_Semaphore);
			}
			vTaskDelay(pdMS_TO_TICKS(150));
		}
		
		
		
	}
	
}

void uart(void *par){
	
	while(1){
		if(xSemaphoreTake(Bot1_Semaphore, pdMS_TO_TICKS(70)) == pdTRUE){//if the mcu2 motor will be off or not
			UART_Transmit_State(temperature,temp_counter,&buttonPressed);
		}
		else{
			UART_Transmit_State(temperature,temp_counter,&buttonPressed);
		}
		
	}
}

void eestate(void *par){
	
	while(1){
		check_State(temperature,&temp_counter,&currentState);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void fan1(void *par){

	while(1){
		handle_State(temperature,DC_fan1,Speed_Scale,&currentState,&reset);
		vTaskDelay(pdMS_TO_TICKS(80));
	}
}

void emergency(void*par){
	//static uint8_t emergency_counter =0;
	
	while(1){
			switch(emergency_flag){
				case 0:
					if(xSemaphoreTake(Emer_Semaphore, pdMS_TO_TICKS(1000)) == pdTRUE){ //waiting to enter the emergency mode
						vTaskSuspend(xHanleUART);
						vTaskSuspend(xHanleEEState);
						vTaskSuspend(xHanleFan1);
						currentState=Emergency_state;
						Speed_Scale=100;
						handle_State(temperature,DC_fan1,Speed_Scale,&currentState,&reset);
						eeprom_write_byte (&EEPROM_State_Add, currentState);
					}
					else{
						//nothing
						vTaskResume(xHanleUART);
						vTaskResume(xHanleEEState);
						vTaskResume(xHanleFan1);
					}
					break;
				case 1:
					if(xSemaphoreTake(Emer_Semaphore, pdMS_TO_TICKS(5)) == pdTRUE){ //checking to exit the emergency mode
						emergency_counter=0;
						emergency_flag=0;
						currentState=Normal_state;
						handle_State(temperature,DC_fan1,Speed_Scale,&currentState,&reset);
						eeprom_write_byte (&EEPROM_State_Add, currentState);
						LED1_OFF();			
						vTaskResume(xHanleUART);
						vTaskResume(xHanleEEState);
						vTaskResume(xHanleFan1);
					}
					else{ //the timeout tick
						emergency_counter++;
						if (emergency_counter>=Emergency_counter_max)
						{
							//WDTCR = (1<<WDE)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0); //resert using watch dog
							// Disable interrupts
							cli();
							LED1_ON();	
							vTaskEndScheduler();
							currentState=Abnormal_state;
							eeprom_write_byte (&EEPROM_State_Add, currentState);
							
							
							WDTCR = (1<<WDE)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0);
							
							while(1){
								emergency_counter++;
							};//to reset
						}
					}
					vTaskDelay(pdMS_TO_TICKS(700));
					break;
					
			}

	}
	
}

/*	Interrupt Service Routine for INT0 (bot1)	 */
ISR(INT0_vect)
{
	bot1_intur++;
	buttonPressed = 1;
	xSemaphoreGive(Bot1_Semaphore);		/* Set the semaphore */
	_delay_ms(50);  	/* Software debouncing control delay */
}




