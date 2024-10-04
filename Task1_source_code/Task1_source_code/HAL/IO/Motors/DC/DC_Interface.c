/*
 * DC_Interface.c
 *
 * Created: 8/12/2024 6:59:00 PM
 *  Author: youefkh05
 */ 

#include "DC_Private.h"

void DC_Initialize(dc_motor motor)
{	
	switch(motor)
	{
		case DC_Motor1:
		DIO_SetPinDirection(DC_Enable_Port, DC_Enable1_Pin, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor1_A1, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor1_A2, DC_OUTPUT);
		// Set Timer1 to Fast PWM mode with 8-bit resolution
		TCCR1A = (1 << WGM10) | (1 << WGM12) | (1 << COM1A1); // Fast PWM, Clear OC1A on Compare Match
		TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);    // Prescaler = 64, start the timer
		break;
		case DC_Motor2:
		DIO_SetPinDirection(DC_Enable_Port, DC_Enable2_Pin, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor2_A3, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor2_A4, DC_OUTPUT);
		break;
	}
	
}

void DC_Start(dc_motor motor, dc_motor_direction direction)
{	
	switch(motor)
	{
		case DC_Motor1:
		DIO_SetPinValue(DC_Enable_Port, DC_Enable1_Pin, DC_HIGH);
		switch(direction)
		{
			case DC_CW:
			DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A1, DC_HIGH);
			DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A2, DC_LOW);
			break;
			case DC_CCW:
			DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A1, DC_LOW);
			DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A2, DC_HIGH);
			break;
		}
		break;
		case DC_Motor2:
		DIO_SetPinValue(DC_Enable_Port, DC_Enable2_Pin, DC_HIGH);
		switch(direction)
		{
			case DC_CW:
			DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A3, DC_HIGH);
			DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A4, DC_LOW);
			break;
			case DC_CCW:
			DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A3, DC_LOW);
			DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A4, DC_HIGH);
			break;
		}
		break;
	}
}

void DC_Stop(dc_motor motor)
{
	switch(motor)
	{
		case DC_Motor1:
		// Stop the pulse
		OCR1A=0;
		DIO_SetPinValue(DC_Enable_Port, DC_Enable1_Pin, DC_LOW);
		DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A1, DC_LOW);
		DIO_SetPinValue(DC_Motor_Port, DC_Motor1_A2, DC_LOW);
		break;
		case DC_Motor2:
		DIO_SetPinValue(DC_Enable_Port, DC_Enable2_Pin, DC_LOW);
		DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A3, DC_LOW);
		DIO_SetPinValue(DC_Motor_Port, DC_Motor2_A4, DC_LOW);
		break;
	}
}

void DC_Change_Speed(dc_motor motor,uint16_t speed)
{	switch (motor){
		case DC_Motor1:
			OCR1A = speed;
		break;
		case DC_Motor2:
			OCR1B = speed/4;
		break;
	}
}
