/*
 * Servo_Configurations.h
 *
 * Created: 10/21/2023 2:07:25 PM
 *  Author: oraga
 */ 


#ifndef SERVO_CONFIGURATIONS_H_
#define SERVO_CONFIGURATIONS_H_

#include "PERIPHERAL_LIBRARY.h"

#define SERVO_PORT PORTD
#define SERVO_PIN  DIO_PIN5

typedef enum
{
	angle_0 = 438,
	angle_P90 = 300,
	angle_N90 = 560
}servo_angle;




#endif /* SERVO_CONFIGURATIONS_H_ */