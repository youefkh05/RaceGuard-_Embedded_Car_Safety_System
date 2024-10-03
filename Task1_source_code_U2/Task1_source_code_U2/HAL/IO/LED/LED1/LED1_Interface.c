/*
 * LED_Interface.c
 *
 * Created: 9/22/2023 9:18:15 AM
 *  Author: oraga
 */ 

#include "LED1_Private.h"



void LED1_Initialize(void)
{
	DIO_SetPinDirection(LED1_PORT, LED1_PIN, LED1_OUTPUT);
}
void LED1_ON(void)
{
	DIO_SetPinValue(LED1_PORT, LED1_PIN, LED1_HIGH);
}
void LED1_OFF(void)
{
	DIO_SetPinValue(LED1_PORT, LED1_PIN, LED1_LOW);
}
void LED1_TGL(void)
{
	DIO_TogglePinValue(LED1_PORT, LED1_PIN);
}