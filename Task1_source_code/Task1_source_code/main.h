/*
 * main.c
 *
 * Created: 8/11/2024 6:15:39 PM
 *  Author: User
 */ 


#ifndef MAIN_H_
#define MAIN_H_

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