/*
* Interrupts_Configuration.h
*
* Created: 10/7/2023 9:14:51 AM
*  Author: oraga
*/


#ifndef INTERRUPTS_CONFIGURATION_H_
#define INTERRUPTS_CONFIGURATION_H_

#include "CPU_CONFIGURATIONS.h"
//#include "Interrupts_Address.h"

typedef enum
{
	INT1_LOW = 0,
	INT1_HIGH = 1,
	INT1_RISING = 2,
	INT1_FALLING = 3
}int1_sense;

typedef enum
{
	INT0_LOW = 0,
	INT0_HIGH = 1,
	INT0_RISING = 2,
	INT0_FALLING = 3
}int0_sense;

typedef enum
{
	INTERRUPT0 = 0,
	INTERRUPT1 = 1,
	INTERRUPT2 = 2
}interrupt_control;





#endif /* INTERRUPTS_CONFIGURATION_H_ */