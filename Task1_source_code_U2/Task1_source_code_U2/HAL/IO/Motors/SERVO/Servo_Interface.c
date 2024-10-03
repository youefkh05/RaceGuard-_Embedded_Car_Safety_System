/*
 * Servo_Interface.c
 *
 * Created: 10/21/2023 2:08:09 PM
 *  Author: oraga
 */ 

#include "Servo_Private.h"

void ServoMotor_Initialize(void)
{
	DIO_SetPinDirection(SERVO_PORT, SERVO_PIN, DIO_OUTPUT);
	TCNT1 = 0;			/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	
}

void ServoMotor_Rotate(servo_angle angle)
{
	OCR1A=((ICR1+1)/4)-angle;
	//_delay_ms(1500);
}
