/*
 * LED1_Private.h
 *
 * Created: 9/22/2023 9:17:31 AM
 *  Author: oraga
 */ 


#ifndef LED1_PRIVATE_H_
#define LED1_PRIVATE_H_

#include "LED1_Configuration.h"


#define S7_DIO_PORT	DIO_PORTD
#define S7_PORT		PORTD



void S7_Init(void);

void S7_write_num(uint8_t num);

void LED1_Initialize(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED1_TGL(void);



#endif /* LED1_PRIVATE_H_ */