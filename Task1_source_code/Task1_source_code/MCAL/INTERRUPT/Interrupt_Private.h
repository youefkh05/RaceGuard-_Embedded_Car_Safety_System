/*
 * Interrupt_Private.h
 *
 * Created: 10/7/2023 9:14:17 AM
 *  Author: oraga
 */ 


#ifndef INTERRUPT_PRIVATE_H_
#define INTERRUPT_PRIVATE_H_

#include "Interrupts_Configuration.h"

void External_Interrupt0_Initalize(int0_sense sense);

void External_Interrupt1_Initalize(int1_sense sense);

void External_Interrupt2_Initalize();


#endif /* INTERRUPT_PRIVATE_H_ */