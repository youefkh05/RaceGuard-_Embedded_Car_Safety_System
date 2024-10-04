/*
 * registers.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Sprints
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_
/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/

#define NULL	((void *)0)

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type8;
typedef volatile uint16* const reg_type16;
typedef float float32;


/************************************************************************/
/*			 			 defining error status             		        */
/************************************************************************/
#define ERROR_STATUS	 		uint8
#define E_OK					0
#define E_NOK					1


/************************************************************************/
/*			  			 defining bool values                         	*/
/************************************************************************/
//typedef uint8 bool;
#define FALSE 					0
#define TRUE 					1


/************************************************************************/
/*			    		 LOW/HIGH defines                 	            */
/************************************************************************/
#define LOW  					0
#define HIGH 					0xFF


/*
 * PORTx registers
 */

#define PORTA_DATA 	*((reg_type8)(0x3B))
#define PORTA_DIR  	*((reg_type8)(0x3A))
#define PORTA_PIN	*((reg_type8)(0x39))

#define PORTB_DATA 	*((reg_type8)(0x38))
#define PORTB_DIR  	*((reg_type8)(0x37))
#define PORTB_PIN	*((reg_type8)(0x36))

#define PORTC_DATA 	*((reg_type8)(0x35))
#define PORTC_DIR  	*((reg_type8)(0x34))
#define PORTC_PIN	*((reg_type8)(0x33))


#define PORTD_DATA 	*((reg_type8)(0x32))
#define PORTD_DIR  	*((reg_type8)(0x31))
#define PORTD_PIN	*((reg_type8)(0x30))










#endif /* REGISTERS_H_ */
