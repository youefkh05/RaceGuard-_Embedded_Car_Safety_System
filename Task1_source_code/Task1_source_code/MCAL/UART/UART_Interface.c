/*
 * UART_Interface.c
 *
 * Created: 10/27/2023 11:28:41 AM
 *  Author: oraga
 */ 
#include "UART_Private.h"

//ezay b4t8l polling fe el main mn 8er ma abwz 7aga
uart_status UART_Initialize_WithoutInterrupt(uart_baudrate baudrate, uart_mode mode, uart_parity parity, uart_datalength length, uart_stopbits stop)
{
	uint16_t UBRR_Val = 0;
	//Define direction of Tx as output
	DDRD |= (1<<PD1);
	//Define direction of Rx as input
	DDRD &=~(1<<PD0);
	//Enable transmit & receive
	UCSRB |= ((1<<RXEN) | (1<<TXEN));
	//Choose data length, mode, parity & stop
	switch(mode)
	{
		case Asynchronous:
		UCSRC &=~ (1<<URSEL);
		break;
		case Synchronous:
		UCSRC |= (1<<URSEL);
		break;
	}
	switch(length)
	{
		case Bits_5:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC &=~ (1<<UCSZ1);
		UCSRC &=~ (1<<UCSZ0);
		break;
		case Bits_6:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC &=~ (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
		case Bits_7:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC &=~ (1<<UCSZ0);
		break;
		case Bits_8:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
		case Bits_9:
		UCSRB |= (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
	}
	switch(parity)
	{
		case Disable:
		UCSRC &=~ (1<<UPM1);
		UCSRC &=~ (1<<UPM0);
		break;
		case Even:
		UCSRC |= (1<<UPM1);
		UCSRC &=~ (1<<UPM0);
		break;
		case Odd:
		UCSRC |= (1<<UPM1);
		UCSRC |= (1<<UPM0);
		break;
	}
	switch(stop)
	{
		case Bit_1:
		UCSRC &=~ (1<<USBS);
		break;
		case Bit_2:
		UCSRC |= (1<<USBS);
		break;
	}
	//Calculate baudrate
	UBRR_Val = (((FREQ) / (16 * baudrate)) - 1);
	UBRRL = UBRR_Val;
	UBRRH = UBRR_Val >> 8;
	return UART_OK;

}
uart_status UART_Transmit_Character(uint8_t data)
{

	while ((!(UCSRA & (1 << UDRE))) ) {
		// Wait until the transmit buffer is empty
	}
	
	UDR = data;
	//while (((UCSRA>>TXC)&0x01) != 1);//Wait until flag of transmitting received
	return UART_OK;
}

uart_status UART_Receive_Character(uint8_t* data)
{
	while (((UCSRA>>RXC)&0x01) != 1);//Wait until flag of receiving received
	*data = UDR;
	return UART_OK;
}

uart_status UART_Transmit_Word(uint16_t data){
	uint8_t high_byte = (data >> 8) & 0xFF;
	uint8_t low_byte = data & 0xFF;
	uart_status s=UART_Transmit_Character(high_byte);
	s|= UART_Transmit_Character(low_byte);
	return s;

}


uart_status UART_Receive_Word(uint16_t* data){
	uint8_t high_byte = 0;
	uint8_t low_byte = 0;
	uart_status s	=	UART_Receive_Character(&high_byte);
	s	|=	UART_Receive_Character(&low_byte);
	*data=Reassemble_uint16(high_byte,low_byte);
	return s;
}

uint16_t Reassemble_uint16(uint8_t high_byte, uint8_t low_byte){
	return ((uint16_t)high_byte << 8) | low_byte;
}

uart_status UART_Transmit_String(uint8_t* str)
{
	while (*str != '\0')
	{
		while (UART_Transmit_Character(*str) != UART_OK);
		str++;
	}
	return UART_OK;
}
uart_status UART_Receive_String(uint8_t* str)
{
	uint8_t null ='\0';
	uint8_t characters = 'D';
	while (characters != '\0')//m4 hy3ml m4akl eny kda m4 h7ot el null char?
	{
		while (UART_Receive_Character(&characters) != UART_OK);
		*str += characters;
	}
	*str += null;
	return UART_OK;
}
uart_status UART_Initialize_WithInterrupt(uart_baudrate baudrate, uart_mode mode, uart_parity parity, uart_datalength length, uart_stopbits stop)
{
	cli();
	uint16_t UBRR_Val = 0;
	//Define direction of Tx as output
	DDRD |= (1<<PD1);
	//Define direction of Rx as input
	DDRD &=~(1<<PD0);
	//Enable transmit, receive & interrupt
	UCSRB |= ((1<<RXEN) | (1<<TXEN) | (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//Choose data length, mode, parity & stop
	switch(mode)
	{
		case Asynchronous:
		UCSRC &=~ (1<<URSEL);
		break;
		case Synchronous:
		UCSRC |= (1<<URSEL);
		break;
	}
	switch(length)
	{
		case Bits_5:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC &=~ (1<<UCSZ1);
		UCSRC &=~ (1<<UCSZ0);
		break;
		case Bits_6:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC &=~ (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
		case Bits_7:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC &=~ (1<<UCSZ0);
		break;
		case Bits_8:
		UCSRB &=~ (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
		case Bits_9:
		UCSRB |= (1<<UCSZ2);
		UCSRC |= (1<<UCSZ1);
		UCSRC |= (1<<UCSZ0);
		break;
	}
	switch(parity)
	{
		case Disable:
		UCSRC &=~ (1<<UPM1);
		UCSRC &=~ (1<<UPM0);
		break;
		case Even:
		UCSRC |= (1<<UPM1);
		UCSRC &=~ (1<<UPM0);
		break;
		case Odd:
		UCSRC |= (1<<UPM1);
		UCSRC |= (1<<UPM0);
		break;
	}
	switch(stop)
	{
		case Bit_1:
		UCSRC &=~ (1<<USBS);
		break;
		case Bit_2:
		UCSRC |= (1<<USBS);
		break;
	}
	//Calculate baudrate
	UBRR_Val = (((FREQ) / (16 * baudrate)) - 1);
	UBRRL = UBRR_Val;
	UBRRH = UBRR_Val >> 8;
	sei();
	return UART_OK;
}
//lw ast3mlt interrupt yb2a kda asyncronus