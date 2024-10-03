#ifndef TWI_REGISTERS_H_
#define TWI_REGISTERS_H_




#define TWAR (*(volatile uint8_t*)(0x22))
#define TWBR (*(volatile uint8_t*)(0x20))
#define TWCR (*(volatile uint8_t*)(0x56))
#define TWDR (*(volatile uint8_t*)(0x23))
#define TWSR (*(volatile uint8_t*)(0x21))




#endif