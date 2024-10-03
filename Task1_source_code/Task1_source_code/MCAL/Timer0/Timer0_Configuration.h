/*
 * Timer0_Configuration.h
 *
 * Created: 11/17/2023 9:44:30 AM
 *  Author: Belal
 */ 


#ifndef TIMER0_CONFIGURATION_H_
#define TIMER0_CONFIGURATION_H_

//#include <Timer0_Addresses.h>
#include "CPU_CONFIGURATIONS.h"


#define MilliSec	1000
#define System_FREQ	8000000/MilliSec
#define Timer0_Bits	256
#define OC0			3
extern uint32_t Overflow_Cycle, CTC_Cycle;

typedef enum
{
	Timer0_NO_Clock = 0,
	Timer0_NO_PRE,
	Timer0_PRE_8,
	Timer0_PRE_64,
	Timer0_PRE_256,
	Timer0_PRE_1024,
	Timer0_Falling,
	Timer0_Rising
}prescale;

typedef enum
{
	PWM_Disconnected = 0,
	PWM_NonInverting,
	PWM_Inverting
}pinmode;

#define PWM0	WGM00
#define CTC0	WGM01
#define I		7 

#endif /* TIMER0_CONFIGURATION_H_ */