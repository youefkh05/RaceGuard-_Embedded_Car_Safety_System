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
		TCNT0 = 0;			/* Set timer0 count zero */
		TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);/* Set Fast PWM with Fosc/64 Timer0 clock */
		break;
		case DC_Motor2:
		DIO_SetPinDirection(DC_Enable_Port, DC_Enable2_Pin, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor2_A3, DC_OUTPUT);
		DIO_SetPinDirection(DC_Motor_Port, DC_Motor2_A4, DC_OUTPUT);
		break;
	}
	
}

void DC_Start(dc_motor motor, dc_motor_direction direction, uint16_t speed)
{	
	switch(motor)
	{
		case DC_Motor1:
		DIO_SetPinValue(DC_Enable_Port, DC_Enable1_Pin, DC_HIGH);
		OCR0 =(speed *250)/ 1024;
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
		OCR0 = 0;
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
			OCR0 =(speed *250)/ 1024;
		break;
		case DC_Motor2:
			OCR1A = speed/4;
		break;
	}
}
