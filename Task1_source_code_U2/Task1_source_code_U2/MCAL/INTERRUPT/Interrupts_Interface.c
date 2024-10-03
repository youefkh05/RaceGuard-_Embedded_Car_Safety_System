/*
* Interrupts_Interface.c
*
* Created: 10/7/2023 9:15:57 AM
*  Author: oraga
*/
#include "Interrupt_Private.h"

void External_Interrupt0_Initalize(int0_sense sense)
{
	// Define interrupt pin INT0 as input 
	CLR_BIT(DDRD,2);	
	// Disable global interrupt while initialization 
	cli();//Clear interrupt, CLR_BIT(SREG,7);
	// Choose sensing method
	switch(sense)
	{
		case INT0_LOW:
		CLR_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00);// 0 0
		break;
		case INT0_HIGH:
		CLR_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00);// 0 1
		break;
		case INT0_FALLING:
		SET_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00);// 1 0
		break;
		case INT0_RISING:
		SET_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00);// 1 1
		break;
		
	}
	// Enable peripheral interrupt 
	SET_BIT(GICR, INT0);
	// Enable global interrupt after initialization 
	sei();//Set interrupt, SET_BIT(SREG,7);
}
void External_Interrupt1_Initalize(int1_sense sense)
{
	// Define interrupt pin INT0 as input 
	CLR_BIT(DDRD,3);
	// Disable global interrupt while initialization 
	cli();//Clear interrupt, CLR_BIT(SREG,7);
	// Choose sensing method
	switch(sense)
	{
		case INT0_LOW:
		CLR_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10);// 0 0
		break;
		case INT0_HIGH:
		CLR_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10);// 0 1
		break;
		case INT0_FALLING:
		SET_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10);// 1 0
		break;
		case INT0_RISING:
		SET_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10);// 1 1
		break;
		
	}
	// Enable peripheral interrupt 
	SET_BIT(GICR, INT0);
	// Enable global interrupt after initialization 
	sei();//Set interrupt, SET_BIT(SREG,7);
}

void External_Interrupt2_Initalize()
{
	// Define interrupt pin INT0 as input
	CLR_BIT(DDRB,2);
	// Disable global interrupt while initialization 
	cli();//Clear interrupt, CLR_BIT(SREG,7);
	CLR_BIT(GICR, INT2);
	CLR_BIT(MCUCSR,ISC2);
	// Enable peripheral interrupt 
	SET_BIT(GICR, INT2);
	// Enable global interrupt after initialization 
	sei();//Set interrupt, SET_BIT(SREG,7);
}
