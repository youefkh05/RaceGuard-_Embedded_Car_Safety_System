/*
 * Interrupts_Address.h
 *
 * Created: 10/7/2023 9:15:15 AM
 *  Author: oraga
 */ 


#ifndef INTERRUPTS_ADDRESS_H_
#define INTERRUPTS_ADDRESS_H_

#define MCUCR  (*(volatile uint8_t*)(0x55))
#define MCUCSR (*(volatile uint8_t*)(0x54))
#define GICR   (*(volatile uint8_t*)(0x5B))
#define GIFR   (*(volatile uint8_t*)(0x5A))
#define SREG   (*(volatile uint8_t*)(0x5F))



#endif /* INTERRUPTS_ADDRESS_H_ */