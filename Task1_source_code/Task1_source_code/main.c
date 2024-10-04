/*
 * main.c
 *
 * Created: 8/11/2024 6:15:39 PM
 *  Author: User
 */ 

#include <xc.h>
#include "main.h"


extern E2PROM_State currentState;
extern uint8_t buttonPressed;
extern uint8_t overflow_count;
extern dc_motor DC_fan1;



/*	Variables	(local but global to debugg)*/
uint8_t reset=0;
volatile uint8_t bot1_intur=0;
volatile uint8_t temp_counter=0;
volatile temp temperature=0;
uint8_t Speed_Scale=250;


void button1(void *par);
void uart(void *par);
void S7_seg(void *par);
void led1(void *par);
void led2(void *par);
void led3(void *par);
void led4(void *par);
void lcd(void *par);
void pot(void *par);
void tmp(void *par);
void eestate(void *par);
void fan1(void *par);

xSemaphoreHandle Bot1_Semaphore;
xSemaphoreHandle S7_Semaphore;
xSemaphoreHandle xMutex;
TaskHandle_t xHanleLED1;
TaskHandle_t xHanleLED2;
TaskHandle_t xHanleLED3;
TaskHandle_t xHanleLED4;
TaskHandle_t xHanlebot1;
TaskHandle_t xHanlepot1;
TaskHandle_t xHanleS7;
TaskHandle_t xHanleLCD;
TaskHandle_t xHanleTMP;
TaskHandle_t xHanleUART;
TaskHandle_t xHanleEEState;
TaskHandle_t xHanleFan1;




int main(void)
{	
	
	App_Init();
	
	//LED_Semaphore=xSemaphoreCreateBinary();
	Bot1_Semaphore=xSemaphoreCreateBinary();
	xSemaphoreTake(Bot1_Semaphore, 0);
	
	

	xTaskCreate(&tmp,"TMP_TASK",100,NULL,0,xHanleTMP);
	xTaskCreate(&uart,"UART_TASK",100,NULL,3,xHanleUART);
	xTaskCreate(&eestate,"EESTATE_TASK",100,NULL,0,xHanleEEState);
	xTaskCreate(&fan1,"FAN1_TASK",100,NULL,2,xHanleFan1);

		
	vTaskStartScheduler();
		
	/*
	//Recieve the message (Speed)
	UART_Receive_Speed(&Speed_Scale);
	*/
		
	//check if need reset
	if(reset==1){
		//Watch dog
		WDT_ON();
	}
		
}

/*	Interrupt Service Routine for INT0 (bot1)	 */
ISR(INT0_vect)
{
	bot1_intur++;
	xSemaphoreGive(Bot1_Semaphore);		/* Set the semaphore */
	_delay_ms(50);  	/* Software debouncing control delay */
}

/*
ISR(TIMER0_OVF_vect){
	
	overflow_count++;
	if (overflow_count >= 16) {
		overflow_count = 0;

		// check the temperature
		if(Read_TEMP_SENSOR()>=50){
			temp_counter++;
		}
	}

}
*/





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
		vTaskDelay(100);
		
		
	}
	
}

void uart(void *par){
	
	while(1){
		UART_Transmit_State(temperature,temp_counter,&buttonPressed);
		vTaskDelay(100);
	}
}

void eestate(void *par){
	
	while(1){
		check_State(temperature,&temp_counter,&currentState);
		vTaskDelay(2000);
	}
}

void fan1(void *par){

	while(1){
		handle_State(temperature,DC_fan1,Speed_Scale,&currentState,&reset);
		vTaskDelay(80);
	}
}






