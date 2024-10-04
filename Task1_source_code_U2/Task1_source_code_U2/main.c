/*
 * main.c
 *
 * Created: 8/14/2024 10:20:44 AM
 *  Author: youefkh05
 */

#include <xc.h>
#include "main.h"

/*		 Global		*/
extern dc_motor DC_mach1;

//variables (LOCAL But golbal to debugg)
extern uint16_t UART_Rdata;
extern volatile E2PROM_State currentState;
extern uint16_t speed;

int main(void)
{	
	App_Init();

	
	/*	Main	Code	*/
    while(1)
    {	
		/* Recieve the message (Temperature)	*/
		UART_Receive_Word(&UART_Rdata);
		
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