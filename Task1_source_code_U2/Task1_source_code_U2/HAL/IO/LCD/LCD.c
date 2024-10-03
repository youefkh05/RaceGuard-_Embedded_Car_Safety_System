

#include "I2C_LCD_PRIVATE.h"


uint8_t global_LCD=0;

static uint8_t PCF8574_write_I2C(uint8_t data) {
	
	
    // Start I2C communication
    uint8_t Local_Error = TWI_SendStartCondition();
    if (Local_Error != NoError) {
        return ERROR;
    }
    
    // Send the device address with write bit
    Local_Error = TWI_SendSlaveAddressWithWrite(slave_address_fixed_bits);
    if (Local_Error != NoError) {
        return ERROR;
    }

    // Send the data byte
    Local_Error = TWI_MasterWriteDataByte(data);
    if (Local_Error!= NoError) {
        return ERROR;
    }

    // Stop I2C communication
    TWI_SendStopCondition();

    return Local_Error;
}



void LCD_initI2C(void) {
    // Initialize your I2C communication
    TWI_voidInitMaster(0x01);  // Replace YOUR_I2C_ADDRESS with the actual address
  // 
    // Perform LCD initialization steps
    LCD_sendCommandI2C(LCD_GO_TO_HOME);            // Return to Home
    LCD_sendCommandI2C(LCD_TWO_LINES_FOUR_BITS_MODE);  // 4-Bit Mode, 2-Row Select
    LCD_sendCommandI2C( LCD_CURSOR_OFF );              // Cursor on, Blinking on
    LCD_sendCommandI2C(LCD_CLEAR_COMMAND);
	 LCD_sendCommandI2C(lcd_EntryMode);           // Clear LCD
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send data to the port which is defined in config.h
* Parameters :
            => Copy_UINT8Data --> Data that you want to display (for every pixel )
* return : nothing
*/
void LCD_SenddataI2C(uint8_t data) {
    // Set RS to indicate data mode
    SET_BIT(global_LCD, LCD_RS_PIN_ID);
	 PCF8574_write_I2C(global_LCD); /* Data Mode RS=1 */

    // Write to PCF8574 to set RS and RW (RW = 0)
	  CLR_BIT(global_LCD, LCD_RW_PIN_ID);
   PCF8574_write_I2C(global_LCD);
   _delay_ms(1);

    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
	_delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (data & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((data & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
     _delay_ms(1);
    // Disable LCD (E=0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID);
   PCF8574_write_I2C(global_LCD);
   _delay_ms(1);
    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
   PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((data & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (data & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
    PCF8574_write_I2C(global_LCD);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	 CLR_BIT(global_LCD, LCD_E_PIN_ID);
	PCF8574_write_I2C(global_LCD); /* Disable LCD E=0 */
	_delay_ms(1); 
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function Interface to send the configuration commands to the LCD Driver
* Parameters :
            => Copy_UINT8Command --> Command number
* return : nothing
*Hint : RS pin Mode is the difference between this function and the previous (LCD_voidSendData)
*/
void LCD_sendCommandI2C(uint8_t command) {
  CLR_BIT(global_LCD,LCD_RS_PIN_ID);
   PCF8574_write_I2C(global_LCD); /* Instruction Mode RS=0 */
 CLR_BIT(global_LCD,LCD_RW_PIN_ID);
   PCF8574_write_I2C(global_LCD); /* write data to LCD so RW=0 */
  _delay_ms(1); /* delay for processing Tas = 50ns */
  SET_BIT(global_LCD,LCD_E_PIN_ID);
  PCF8574_write_I2C(global_LCD);  /* Enable LCD E=1 */
  _delay_ms(1);

    // Prepare the data based on LCD_LAST_PORT_PINS configuration
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | (command & 0xF0);
    #else
        global_LCD = (global_LCD & 0xF0) | ((command & 0xF0) >> 4);
    #endif

    // Send data from PCF8574 to LCD PORT
   PCF8574_write_I2C(global_LCD);
  _delay_ms(1); 
    // Disable LCD (E=0)
    CLR_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
    _delay_ms(1);
    // Enable LCD (E=1)
    SET_BIT(global_LCD, LCD_E_PIN_ID);
    PCF8574_write_I2C(global_LCD);
   _delay_ms(1); 
    // Prepare the data for the second nibble
    #ifdef LCD_LAST_PORT_PINS
        global_LCD = (global_LCD & 0x0F) | ((command & 0x0F) << 4);
    #else
        global_LCD = (global_LCD & 0xF0) | (command & 0x0F);
    #endif

    // Send data from PCF8574 to LCD PORT
	 PCF8574_write_I2C(global_LCD);

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLR_BIT(global_LCD,LCD_E_PIN_ID);
	 PCF8574_write_I2C(global_LCD);   /* Disable LCD E=0 */
	_delay_ms(1);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send string to the port which is defined in config.h
* Parameters :
            => * Copy_UINT8ptrString  --> Pointer to the string
* return : nothing
*/
void LCD_voidSendString  ( const uint8_t * Copy_UINT8ptrString ){

	uint8_t LOC_UINT8Iterator = 0 ;

	while( Copy_UINT8ptrString[LOC_UINT8Iterator] != '\0' ){

		LCD_SenddataI2C( Copy_UINT8ptrString[LOC_UINT8Iterator] );
		LOC_UINT8Iterator++ ;

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send number to the port which is defined in config.h
* Parameters :
            => Copy_UINT64Number --> number that you want to display
* return : nothing
*/
void LCD_voidSendNumber   ( uint64_t Copy_UINT64Number    ){

	uint64_t LOC_UINT64Reversed = 1 ;

	if( Copy_UINT64Number == 0 ){ LCD_SenddataI2C('0'); }

	else{

		while( Copy_UINT64Number != 0 ){

			LOC_UINT64Reversed = ( LOC_UINT64Reversed * 10 ) + ( Copy_UINT64Number % 10 );
			Copy_UINT64Number /= 10 ;

		}
		while( LOC_UINT64Reversed != 1 ){

			LCD_SenddataI2C( ( LOC_UINT64Reversed % 10 ) + 48 );
			LOC_UINT64Reversed /= 10 ;

		}

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function set the curser position
* Parameters :
            => Copy_UINT8Row --> row number (LCD_ROW_1 or LCD_ROW_2)
			=> Copy_UINT8Col --> column number (LCD_COL_1 ... LCD_COL_16)
* return : nothing
*Hint :-
   In This function we send a command which =0b1xxxxxxx
   MSB = 1  ===> refers that it is command to set cursor
   xxxxxxx  ===> refers to AC ( Address Counter 7Bits / DDRAM Locations 128Location )
*/
void LCD_voidSetPosition ( uint8_t Copy_UINT8Row , uint8_t Copy_UINT8Col ){

	uint8_t LOC_UINT8data ;

	/* In These cases will set at (0,0) ==> if the user enter invalid location */
	if(Copy_UINT8Row>2||Copy_UINT8Row<1||Copy_UINT8Col>16||Copy_UINT8Col<1)  //check
	{
		LOC_UINT8data = LCD_SET_CURSOR_LOCATION   ;   // first location 
	}

	else if( Copy_UINT8Row == LCD_ROW_1 ){

		LOC_UINT8data = ( ( LCD_SET_CURSOR_LOCATION   ) + ( Copy_UINT8Col - 1 ) );              //Row1 -> 0x80+col-1

	}

	else if( Copy_UINT8Row == LCD_ROW_2 ){

		LOC_UINT8data = ( ( LCD_SET_CURSOR_LOCATION   ) + (64) + ( Copy_UINT8Col - 1 ) );       //Row2 -> 0xc0+col-1

	}
	LCD_sendCommandI2C ( LOC_UINT8data );
	_delay_ms(1);

}




//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function clear LCD
* Parameters : nothing
* return : nothing
*/
void LCD_voidClearScreen(void)
{
	LCD_sendCommandI2C(LCD_CLEAR_COMMAND );
	_delay_ms(10); //wait more than 1.53 ms
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
/*
* Breif : This Function send a pulse (falling edge ) to Enable Pin
* Parameters : nothing
* return : nothing
*
* Hint : static Function to forbid calling it out this file
*
*/

void ClearLCDLine(uint8_t line) {
	uint8_t LOC_UINT8data;
	if (line == LCD_ROW_1) {
		LOC_UINT8data = LCD_SET_CURSOR_LOCATION  ; // Row1
		} else if (line == LCD_ROW_2) {
		LOC_UINT8data = LCD_SET_CURSOR_LOCATION   + 64; // Row2
		} else {
		LOC_UINT8data = LCD_SET_CURSOR_LOCATION  ; // Default to Row1 for invalid input
	}

	LCD_sendCommandI2C(LOC_UINT8data); // Set cursor to the beginning of the specified line

	for (uint8_t i = 0; i < 16; i++) {
		LCD_SenddataI2C(' '); // Fill the line with empty spaces
	}
}
void displayNumberWithLeadingZeros(uint8_t number) {
	if (number < 10) {
		// Display two leading zeros if the number is less than 10
		LCD_voidSendNumber(0);
		LCD_voidSendNumber(0);
	}
     else if (number < 100) {
	     // Display an additional leading zero if the number is less than 100
	     LCD_voidSendNumber(0);
     }
	LCD_voidSendNumber(number);
}