/*
 * APP.c
 *
 * Created: 8/13/2024 6:51:38 PM
 *  Author: youefkh05
 */ 

#include "APP.h"

// Global variables
E2PROM_State currentState =Normal_state;
uint8_t buttonPressed = 0;
uint8_t overflow_count=0;
dc_motor DC_fan1=DC_Motor1;

uint8_t EEPROM_State_Add=0b01000000;	//any place

void App_Init(void){
	/*		Initializations		*/
	DC_Initialize(DC_fan1);
	Initialize_E2PROM_State();
	Initialize_TEMP_SENSOR();
	ADC_Initialize(5,1024);
	
	DIO_SetPinDirection(BOT1_PORT,BOT1_PIN,DIO_INPUT); //push button
	//Timer0_OVF_WithInterrupt_Initialize();
	
	uart_status UART_State= UART_Initialize_WithoutInterrupt(UART_9600,Synchronous, Disable , Bits_8, Bit_1);
	if(UART_State==UART_NOK){
		return 0;
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
		//Timer0_OVF_WithInterrupt_Stop();
	}
	else if(T>=50.0 && *S==Normal_state){
		*S=Emergency_state;
		eeprom_write_byte (&EEPROM_State_Add, *S);
		//Timer0_OVF_WithInterrupt_Start(Timer0_PRE_1024);
	}
	
	 // 7 seconds elapsed on emergency
	if(*counter>=Emergency_counter_max && *S!=Abnormal_state){
		*S=Abnormal_state;
		eeprom_write_byte (&EEPROM_State_Add, *S);
		//Timer0_OVF_WithInterrupt_Stop();
	}
	
}

void handle_State(temp T,dc_motor DC_fan,uint8_t Speed,E2PROM_State* S,uint8_t* reset){
	switch (*S){
		case Normal_state:
			//as we are normal
			//Timer0_OVF_WithInterrupt_Stop();
			if(T<=20.0){
				DC_Stop(DC_fan);
			}
			else if (T>20.0 && T<=40.0){
				//increase fan speed
				DC_Start(DC_fan,DC_CW);
				DC_Change_Speed(DC_fan,(temp)T*4*(Speed/250));
			}
			else if (T>40 &&T<=50) {
				//max speed
				DC_Start(DC_fan,DC_CW);
				DC_Change_Speed(DC_fan,40*4);
			}
			else{
				//nothing
			}
		break;
		case Emergency_state:
			//max speed
			DC_Start(DC_fan,DC_CW);
			DC_Change_Speed(DC_fan,40*4);
			
		break;
		case Abnormal_state:
			//max speed
			DC_Start(DC_fan,DC_CW);
			DC_Change_Speed(DC_fan,40*4);
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
			uart_status x=UART_Transmit_Word(Emergency_Mes);
		} 
		else
		{
			//Abnormal
			uart_status x=UART_Transmit_Word(Abnormal_Mes);
		}

	}
	else if (T>40 && T<=50 && *bot1f==1)
	{	
		//send the off signal
		uart_status x=UART_Transmit_Word(Off_Mes);
	}
	else{
		/* Reset the flag	*/
		*bot1f=0;
		uart_status x=UART_Transmit_Word(T);
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