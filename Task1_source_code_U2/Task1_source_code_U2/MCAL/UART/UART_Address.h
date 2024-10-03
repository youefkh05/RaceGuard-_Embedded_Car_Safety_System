/*
 * UART_Address.h
 *
 * Created: 10/27/2023 11:27:59 AM
 *  Author: oraga
 */ 


#ifndef UART_ADDRESS_H_
#define UART_ADDRESS_H_

#define UDR   (*(volatile uint8_t*)(0x2C))
#define UCSRA (*(volatile uint8_t*)(0x2B))
#define UCSRB (*(volatile uint8_t*)(0x2A))
#define UCSRC (*(volatile uint8_t*)(0x40))
#define UBRRH (*(volatile uint8_t*)(0x40))
#define UBRRL (*(volatile uint8_t*)(0x29))






#endif /* UART_ADDRESS_H_ */