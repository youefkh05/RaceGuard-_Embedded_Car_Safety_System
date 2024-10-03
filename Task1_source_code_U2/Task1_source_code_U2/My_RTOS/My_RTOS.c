/*
 * My_RTOS.c
 *
 * Created: 9/26/2024 9:31:31 AM
 *  Author: User
 */ 

#include "My_RTOS.h"

task_t arr[TASKS_NUM];

uint32_t max_per=0;

void My_RTOS_Init(void){
	for(uint8_t i=0;i<TASKS_NUM;i++)
		arr[i].per=0;
	Timer0_OVF_WithInterrupt_Initialize();
}


void start_My_RTOS(void){
	Timer0_OVF_WithInterrupt_Start(Timer0_PRE_8);
}

void create_my_task(void (*task_fun)(void),uint32_t per, uint8_t pior){
	if(per>max_per)
		max_per=per;
	arr[pior].per=per;
	arr[pior].task_fun=task_fun;
}



ISR(TIMER0_OVF_vect){
	static uint32_t count=0;
	count++;
	if (count >= max_per) 
		count = 0;
		
	for(uint8_t i=0;i<TASKS_NUM;i++){
		if(0==(count%arr[i].per))
			if(NULL!=arr[i].task_fun)
				arr[i].task_fun();
		
	}
	

}