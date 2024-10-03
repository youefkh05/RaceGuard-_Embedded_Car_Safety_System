/*
 * LED5_Interface.c
 *
 * Created: 9/22/2023 9:21:23 AM
 *  Author: oraga
 */ 

#include "LED5_Private.h"

void LED5_Initialize(void)
{
	DIO_SetPinDirection(LED5_PORT, LED5_PIN, LED5_OUTPUT);
}
void LED5_ON(void)
{
	DIO_SetPinValue(LED5_PORT, LED5_PIN, LED5_HIGH);
}
void LED5_OFF(void)
{
	DIO_SetPinValue(LED5_PORT, LED5_PIN, LED5_LOW);
}
void LED5_TGL(void)
{
	DIO_TogglePinValue(LED5_PORT, LED5_PIN);
}