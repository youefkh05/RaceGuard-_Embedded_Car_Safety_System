/*
 * LED4_Interface.c
 *
 * Created: 9/22/2023 9:21:23 AM
 *  Author: oraga
 */ 

#include "LED4_Private.h"

void LED4_Initialize(void)
{
	DIO_SetPinDirection(LED4_PORT, LED4_PIN, LED4_OUTPUT);
}
void LED4_ON(void)
{
	DIO_SetPinValue(LED4_PORT, LED4_PIN, LED4_HIGH);
}
void LED4_OFF(void)
{
	DIO_SetPinValue(LED4_PORT, LED4_PIN, LED4_LOW);
}
void LED4_TGL(void)
{
	DIO_TogglePinValue(LED4_PORT, LED4_PIN);
}