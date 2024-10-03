/*
 * My_RTOS.h
 *
 * Created: 9/26/2024 9:31:16 AM
 *  Author: User
 */ 


#ifndef MY_RTOS_H_
#define MY_RTOS_H_

#include "Timer0_Private.h"

/*-------------------------------STANDARD TYPES-------------------------------*/
typedef unsigned char uint8_t;
//typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long int uint64_t;


#define  TASKS_NUM	10

typedef struct task
{
	uint32_t per;
	void (*task_fun)(void);
}task_t;

void My_RTOS_Init(void);

void create_my_task(void (*task_fun)(void),uint32_t per, uint8_t pior);

void start_My_RTOS(void);


#endif /* MY_RTOS_H_ */