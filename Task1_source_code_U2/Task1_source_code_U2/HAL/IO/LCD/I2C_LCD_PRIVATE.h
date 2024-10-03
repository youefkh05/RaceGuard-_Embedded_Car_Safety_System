#ifndef I2C_LCD_PRIVATE_H_
#define I2C_LCD_PRIVATE_H_

#include "I2C_LCD_INTERFACE.h"

 

void LCD_initI2C(void) ;
void LCD_SenddataI2C(uint8_t data);
void LCD_sendCommandI2C(uint8_t command);
void LCD_voidSendString  ( const uint8_t * Copy_UINT8ptrString );
void LCD_voidSendNumber   ( uint64_t Copy_UINT64Number    );
void LCD_voidSetPosition ( uint8_t Copy_UINT8Row , uint8_t Copy_UINT8Col );
void LCD_voidClearScreen(void);
void ClearLCDLine(uint8_t line);
void displayNumberWithLeadingZeros(uint8_t number);

#endif /* CLCD_PRIVATE_H_ */