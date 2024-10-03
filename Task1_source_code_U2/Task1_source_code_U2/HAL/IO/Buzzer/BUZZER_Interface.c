/*
 * BUZZER_Interface.c
 *
 * Created: 8/16/2024	11:19:40 AM
 *  Author: youefkh05
 */

#include "BUZZER_Private.h"



void BUZZER_Initialize(void)
{
	DIO_SetPinDirection(BUZZER_PORT, BUZZER_PIN, BUZZER_OUTPUT);
}
void BUZZER_ON(void)
{
	DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, BUZZER_HIGH);
}
void BUZZER_OFF(void)
{
	DIO_SetPinValue(BUZZER_PORT, BUZZER_PIN, BUZZER_LOW);
}
void BUZZER_TGL(void)
{
	DIO_TogglePinValue(BUZZER_PORT, BUZZER_PIN);
}