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
	
	//ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	sei();  // Enable global interrupts
	TCNT1 = 0;			/* Set timer1 count zero */
	ICR1 = 19999;  // Set top value for 20 ms period (50Hz)
}

void ServoMotor_Rotate(uint8_t angle)
{
	// Map the angle (0-180) to the required pulse width (1000-2000 us)
	uint16_t pulse_width = (angle * 11) + 1000;
	
	// Set the pulse width to control the position of the servo
	OCR1A = pulse_width;
	
	//OCR1A=((ICR1+1)/4)-angle;
	//_delay_ms(1500);
}
