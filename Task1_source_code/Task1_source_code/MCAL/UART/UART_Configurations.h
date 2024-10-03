/*
 * UART_Configurations.h
 *
 * Created: 10/27/2023 11:28:27 AM
 *  Author: oraga
 */ 


#ifndef UART_CONFIGURATIONS_H_
#define UART_CONFIGURATIONS_H_
//#include "UART_Address.h"
#include "CPU_CONFIGURATIONS.h"

#define FREQ   160000
//UART BaudRate
typedef enum
{
	UART_9600 = 96,
	UART_38400 = 384,
	UART_115200 = 1152
}uart_baudrate;
//UART mode
typedef enum
{
	Asynchronous = 0,
	Synchronous = 1
}uart_mode;
//UART Parity
typedef enum
{
	Disable = 0,
	Even = 1,
	Odd = 2
}uart_parity;
//UART Stop Bits
typedef enum
{
	Bit_1 = 0,
	Bit_2 = 1
}uart_stopbits;
//UART Data Modes
typedef enum
{
	Bits_5 = 0,
	Bits_6 = 1,
	Bits_7 = 2,
	Bits_8 = 3,
	Bits_9 = 4
}uart_datalength;
//UART Status
typedef enum
{
	UART_NOK = 0,
	UART_OK = 1
}uart_status;


#endif /* UART_CONFIGURATIONS_H_ */