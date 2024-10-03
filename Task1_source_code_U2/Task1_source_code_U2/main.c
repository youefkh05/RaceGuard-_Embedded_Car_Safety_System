/*
 * main.c
 *
 * Created: 8/14/2024 10:20:44 AM
 *  Author: youefkh05
 */

#include <xc.h>
#include "main.h"

//variables (LOCAL But golbal to debugg)
uint16_t UART_Rdata=0;
volatile E2PROM_State currentState =Normal_state;
uint16_t speed=0;

int main(void)
{	
	/*		Initializations		*/
	
	dc_motor DC_mach1=DC_Motor1;
	DC_Initialize(DC_mach1);
	ServoMotor_Initialize();
	LED1_Initialize();
	LED2_Initialize();
	LED3_Initialize();
	//LED4_Initialize();
	BUZZER_Initialize();
	ADC_Initialize(5, 1024);
	uart_status UART_State= UART_Initialize_WithoutInterrupt(UART_9600,Synchronous, Disable , Bits_8, Bit_1);
	if(UART_State==UART_NOK){
		return 0;
	}
	
	
	
	
	//Start the machine
	ServoMotor_Rotate(angle_0);
	DC_Start(DC_mach1,DC_CW);

	
	/*	Main	Code	*/
    while(1)
    {	
		/* Recieve the message (Temperature)	*/
		UART_State= UART_Receive_Word(&UART_Rdata);
		
		speed=ADC_Read(POT1_PIN);
		
		DC_Change_Speed(DC_mach1,speed);
		/*
		//Send the message (Speed)	
		UART_Transmit_Speed(speed);
		*/
		
		/* Handle the message	*/
		handle_Mes(UART_Rdata,DC_mach1,&currentState);
    }
}

/*
ISR(USART_RXC_vect)
{
	//Read the data from buffer
	if(highf==0)
		high=UDR;
	else
		low=UDR;
	//Clear the interrupt flag
	UCSRA|=(1<<RXC);
	highf=!highf;
}
*/