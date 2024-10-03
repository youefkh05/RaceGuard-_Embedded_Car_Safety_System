/*
 * UART_Private.h
 *
 * Created: 10/27/2023 11:28:12 AM
 *  Author: oraga
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include "UART_Configurations.h"

uart_status UART_Initialize_WithoutInterrupt(uart_baudrate baudrate, uart_mode mode, uart_parity parity, uart_datalength length, uart_stopbits stop);
uart_status UART_Transmit_Character(uint8_t data);
uart_status UART_Receive_Character(uint8_t* data);
uart_status UART_Transmit_Word(uint16_t data);
uart_status UART_Receive_Word(uint16_t* data);
uint16_t Reassemble_uint16(uint8_t high_byte, uint8_t low_byte);

uart_status UART_Transmit_String(uint8_t* str);
uart_status UART_Receive_String(uint8_t* str);

uart_status UART_Initialize_WithInterrupt(uart_baudrate baudrate, uart_mode mode, uart_parity parity, uart_datalength length, uart_stopbits stop);


#endif /* UART_PRIVATE_H_ */