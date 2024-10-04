/*
 * main.h
 *
 * Created: 8/14/2024 10:20:44 AM
 *  Author: youefkh05
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define BOT1_PORT	PORTB
#define BOT1_PIN	DIO_PIN0

#ifndef F_CPU
#define F_CPU	(8000000L)
#endif


#include "PERIPHERAL_LIBRARY.h"
#include "MODULE_LIBRARY.h"
#include "APP.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#endif /* MAIN_H_ */