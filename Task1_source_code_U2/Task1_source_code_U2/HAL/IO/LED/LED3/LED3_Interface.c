/*
 * LED3_Interface.c
 *
 * Created: 9/22/2023 9:21:23 AM
 *  Author: oraga
 */ 

#include "LED3_Private.h"

void LED3_Initialize(void)
{
	DIO_SetPinDirection(LED3_PORT, LED3_PIN, LED3_OUTPUT);
}
void LED3_ON(void)
{
	DIO_SetPinValue(LED3_PORT, LED3_PIN, LED3_HIGH);
}
void LED3_OFF(void)
{
	DIO_SetPinValue(LED3_PORT, LED3_PIN, LED3_LOW);
}
void LED3_TGL(void)
{
	DIO_TogglePinValue(LED3_PORT, LED3_PIN);
}