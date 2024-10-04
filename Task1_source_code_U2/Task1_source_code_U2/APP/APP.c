/*
 * APP.c
 *
 * Created: 8/13/2024 6:51:38 PM
 *  Author: youefkh05
 */ 

#include "APP.h"

/*		 Global		*/
dc_motor DC_mach1=DC_Motor1;

//variables (LOCAL But golbal to debugg)
uint16_t UART_Rdata=0;
volatile E2PROM_State currentState =Normal_state;
uint16_t speed=0;

void App_Init(void){
	/*		Initializations		*/
	DC_Initialize(DC_mach1);
	ServoMotor_Initialize();
	LED1_Initialize();
	LED2_Initialize();
	LED3_Initialize();
	//LED4_Initialize();
	BUZZER_Initialize();
	ADC_Initialize(AVCC,ADC_PRE0);
	uart_status UART_State= UART_Initialize_WithoutInterrupt(UART_9600,Synchronous, Disable , Bits_8, Bit_1);
	if(UART_State==UART_NOK){
		return ;
	}
	
	//Start the machine
	ServoMotor_Rotate(90);
	DC_Start(DC_mach1,DC_CW);
}

void handle_Mes(temp T,dc_motor DC_MOT, E2PROM_State* S){
	
	// off all LED and Buzzer
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	BUZZER_OFF();
	DC_Start(DC_MOT,DC_CW);
	
	if(T<=20.0){
		LED3_ON();
		*S=Normal_state;
	}
	else if (T>20.0 && T<=40.0){
		LED2_ON();
		*S=Normal_state;
	}
	else if (T>40.0 && T<=50.0){
		LED1_ON();
	}
	else if (T==Off_Mes)
	{
		*S=Off_state;
		LED1_ON();
		DC_Stop(DC_MOT);
	}
	else if (T==Emergency_Mes)
	{
		*S=Emergency_state;
		LED1_ON();
		BUZZER_ON();
	}
	else if (T==Abnormal_Mes)
	{
		*S=Abnormal_Mes;
		LED1_ON();
		BUZZER_ON();
		DC_Stop(DC_MOT);
		ServoMotor_Rotate(90);
		
	}
	else {
		//for debugg
		LED1_ON();
		LED2_ON();
		LED3_ON();
		*S=Emergency_state;
	}
}

void UART_Transmit_Speed(uint16_t speed){
	// the scale is from 0-250
	uint8_t x= 250*speed/1023;
	UART_Transmit_Character(x);
}