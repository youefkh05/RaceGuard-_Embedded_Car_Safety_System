/*
 * LED2_Interface.c
 *
 * Created: 9/22/2023 9:21:23 AM
 *  Author: oraga
 */ 

#include "LED2_Private.h"

void LED2_Initialize(void)
{
	DIO_SetPinDirection(LED2_PORT, LED2_PIN, LED2_OUTPUT);
}
void LED2_ON(void)
{
	DIO_SetPinValue(LED2_PORT, LED2_PIN, LED2_HIGH);
}
void LED2_OFF(void)
{
	DIO_SetPinValue(LED2_PORT, LED2_PIN, LED2_LOW);
}
void LED2_TGL(void)
{
	DIO_TogglePinValue(LED2_PORT, LED2_PIN);
}