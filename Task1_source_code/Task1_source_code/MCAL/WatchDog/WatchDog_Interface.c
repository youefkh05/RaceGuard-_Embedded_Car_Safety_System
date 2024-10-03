/*
* WatchDog_Interface.c
*
 * Created: 8/16/2024	10:02:25 PM
 *  Author: youefkh05
 */

#include "Timer0_Private.h"

void WDT_ON()
{
	/*
	Watchdog timer enables with typical timeout period 2.1 
	second.
	*/
	WDTCR = (1<<WDE);
	WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
}

void WDT_OFF()
{
	/*
	This function use for disable the watchdog timer.
	*/
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}