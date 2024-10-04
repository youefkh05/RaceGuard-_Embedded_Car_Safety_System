/*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/
 /*****************************************************************************/

#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;


//#define LCD_MODE  FOUR_BIT

/*
 * choose control pins
 */
#define RS_PIN	DIO_PIN1
#define RS_PORT	DIO_PORTA


#define EN_PIN   DIO_PIN3
#define EN_PORT  DIO_PORTA


/*
 * data pins
 */
#define D7_PIN    DIO_PIN4
#define D7_PORT   DIO_PORTB

#define D6_PIN    DIO_PIN3
#define D6_PORT   DIO_PORTB

#define D5_PIN    DIO_PIN2
#define D5_PORT   DIO_PORTB

#define D4_PIN    DIO_PIN1
#define D4_PORT   DIO_PORTB






#endif
