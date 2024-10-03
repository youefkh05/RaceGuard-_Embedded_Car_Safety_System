/*
* Timer0_Interface.c
*
* Created: 11/17/2023 9:45:01 AM
*  Author: Belal
*/
#include "Timer0_Private.h"

uint32_t Overflow_Cycle = 0, CTC_Cycle = 0;

void Timer0_OVF_WithoutInterrupt_Initialize(void)
{
	
	CLR_BIT(TCCR0, CTC0);
	CLR_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TIMSK, TOIE0);
}
void Timer0_OVF_WithoutInterrupt_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 0;
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 1/System_FREQ;
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 8 / System_FREQ;
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 64 / System_FREQ;
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		Overflow_Cycle = 256 / System_FREQ;
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		Overflow_Cycle = 1024 / System_FREQ;
		break;
		default:
		break;
	}
}
void Timer0_OVF_WithoutInterrupt_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	Overflow_Cycle = 0;
}
void Timer0_OVF_WithoutInterrupt_SetDelay(uint32_t Delay)
{
	uint32_t Counter = 0, Count = Delay/Overflow_Cycle, Overflows = (Count/Timer0_Bits) + 1;
	TCNT0 = Timer0_Bits - (Count % Timer0_Bits);
	while(Counter != Overflows)
	{
		while(!Get_Bit(TIFR, TOV0));
		CLR_BIT(TIFR, TOV0);
		Counter++;
	}
}
void Timer0_OVF_WithInterrupt_Initialize(void)
{
	CLR_BIT(TCCR0, PWM0);
	CLR_BIT(TCCR0, CTC0);
	CLR_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
	SET_BIT(TIMSK, TOIE0);
	SET_BIT(SREG, I);
}
void Timer0_OVF_WithInterrupt_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 0;
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 1/System_FREQ;
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 8/System_FREQ;
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		Overflow_Cycle = 64/System_FREQ;
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		Overflow_Cycle = 256/System_FREQ;
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		Overflow_Cycle = 1024/System_FREQ;
		break;
		default:
		break;
	}
}
void Timer0_OVF_WithInterrupt_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	Overflow_Cycle = 0;
}
void Timer0_OVF_WithInterrupt_SetDelay(uint32_t Delay)
{
	uint32_t Count = Delay/Overflow_Cycle, Overflows = (Count/Timer0_Bits) + 1;
	TCNT0 = Timer0_Bits - (Count % Timer0_Bits);
}

void Timer0_CTC_WithoutInterrupt_Initialize(void)
{
	CLR_BIT(TCCR0, PWM0);
	SET_BIT(TCCR0, CTC0);
	CLR_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
	CLR_BIT(TIMSK, OCIE0);
}
void Timer0_CTC_WithoutInterrupt_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 0;
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 1/System_FREQ;
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 8/System_FREQ;
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 64/System_FREQ;
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		CTC_Cycle = 256/System_FREQ;
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		CTC_Cycle = 1024/System_FREQ;
		break;
		default:
		break;
	}
}
void Timer0_CTC_WithoutInterrupt_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	CTC_Cycle = 0;
}
void Timer0_CTC_WithoutInterrupt_SetDelay(uint32_t Delay , uint8_t OCR)
{
	uint32_t Counter = 0, Count = Delay/CTC_Cycle, CTCs = (Count/OCR) + 1;
	OCR0 = OCR;
	TCNT0 = OCR - (Count % OCR);
	while(Counter != CTCs)
	{
		while(!Get_Bit(TIFR, OCF0));
		CLR_BIT(TIFR, OCF0);
		Counter++;
	}
}
void Timer0_CTC_WithInterrupt_Initialize(void)
{
	CLR_BIT(TCCR0, PWM0);
	SET_BIT(TCCR0, CTC0);
	CLR_BIT(TCCR0, COM00);
	CLR_BIT(TCCR0, COM01);
	SET_BIT(TIMSK, OCIE0);
	SET_BIT(SREG, I);
}
void Timer0_CTC_WithInterrupt_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 0;
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 1/System_FREQ;
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 8/System_FREQ;
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		CTC_Cycle = 64/System_FREQ;
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		CTC_Cycle = 256/System_FREQ;
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		CTC_Cycle = 1024/System_FREQ;
		break;
		default:
		break;
	}
}
void Timer0_CTC_WithInterrupt_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
	CTC_Cycle = 0;
}
void Timer0_CTC_WithInterrupt_SetDelay(uint32_t Delay, uint8_t OCR)
{
	uint32_t Count = Delay/CTC_Cycle, CTCs = (Count/OCR) + 1;
	OCR0 = OCR;
	TCNT0 = OCR - (Count % OCR);
}

void Timer0_FPWM_Initialize(void)
{
	SET_BIT(DDRB, OC0);
	SET_BIT(TCCR0, PWM0);
	SET_BIT(TCCR0, CTC0);
}
void Timer0_FPWM_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
		default:
		break;
	}
}
void Timer0_FPWM_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}
void Timer0_FPWM_SetDuty(pinmode Pinmode, uint8_t Dutycycle)
{
	switch(Pinmode)
	{
		case PWM_Disconnected:
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);
		break;
		case PWM_NonInverting:
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		OCR0 = ((Timer0_Bits * Dutycycle) / 100) - 1;
		break;
		case PWM_Inverting:
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		OCR0 = Timer0_Bits - (((Timer0_Bits * Dutycycle) / 100) - 1);
		break;
		default:
		break;
	}
}

void Timer0_PPWM_Initialize(void)
{
	SET_BIT(DDRB, OC0);
	SET_BIT(TCCR0, PWM0);
	CLR_BIT(TCCR0, CTC0);
}
void Timer0_PPWM_Start(prescale Prescale)
{
	switch(Prescale)
	{
		case Timer0_NO_Clock:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_NO_PRE:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_8:
		CLR_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_64:
		SET_BIT(TCCR0, CS00);
		SET_BIT(TCCR0, CS01);
		CLR_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_256:
		CLR_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
		case Timer0_PRE_1024:
		SET_BIT(TCCR0, CS00);
		CLR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS02);
		break;
		default:
		break;
	}
}
void Timer0_PPWM_Stop(void)
{
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}
void Timer0_PPWM_SetDuty(pinmode Pinmode, uint8_t Dutycycle)
{
	switch(Pinmode)
	{
		
		case PWM_Disconnected:
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);
		break;
		case PWM_NonInverting:
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		OCR0 = ((Timer0_Bits * Dutycycle)/100) - 1;
		break;
		case PWM_Inverting:
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		OCR0 = Timer0_Bits - (((Timer0_Bits * Dutycycle)/100) - 1);
		break;
		default:
		break;
	}
}