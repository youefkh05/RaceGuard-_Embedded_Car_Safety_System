/*
 * LED_Interface.c
 *
 * Created: 9/22/2023 9:18:15 AM
 *  Author: oraga
 */ 

#include "LED1_Private.h"

static char num_arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

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

void S7_Init(void){
	DIO_SetPortDirection(S7_DIO_PORT,DIO_OUTPUT);
}

void S7_write_num(uint8_t num){
	S7_PORT=num_arr[num];
}