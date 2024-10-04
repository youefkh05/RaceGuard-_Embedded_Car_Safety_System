/*
 * main.c
 *
 * Created: 8/11/2024 6:15:39 PM
 *  Author: User
 */ 

#include <xc.h>
#include "main.h"


int main(void)
{	
	
	App_Init();
	Free_RTOS_Init();
	

		
	vTaskStartScheduler();
		
	/*ddd
	//Recieve the message (Speed)
	UART_Receive_Speed(&Speed_Scale);
	*/
	

}








