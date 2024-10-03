/*
 * main.c
 *
 * Created: 8/11/2024 6:15:39 PM
 *  Author: User
 */ 

#include <xc.h>
#include "main.h"

// Global variables
volatile E2PROM_State currentState =Normal_state;
volatile uint8_t buttonPressed = 0;
volatile uint8_t overflow_count=0;
/*	Variables	(local but global to debugg)*/
uint8_t reset=0;
volatile uint8_t bot1_intur=0;
volatile uint8_t temp_counter=0;
volatile temp temperature=0;
uint8_t Speed_Scale=250;

xSemaphoreHandle LED_Semaphore;
xSemaphoreHandle LCD_Semaphore;
xSemaphoreHandle S7_Semaphore;//J
xSemaphoreHandle xMutex;
TaskHandle_t xHanleLED1;
TaskHandle_t xHanleLED2;
TaskHandle_t xHanleLED3;
TaskHandle_t xHanleLED4;
TaskHandle_t xHanlebot1;
TaskHandle_t xHanlepot1;
TaskHandle_t xHanleS7;
TaskHandle_t xHanleLCD;
TaskHandle_t xHanleTMP;





int main(void)
{	
	
	LED_Semaphore=xSemaphoreCreateBinary();
	LCD_Semaphore=xSemaphoreCreateBinary();
	
	/*		Initializations		*/
	dc_motor DC_fan1=DC_Motor1;
	DC_Initialize(DC_fan1);
	Initialize_E2PROM_State();
	Initialize_TEMP_SENSOR();
	ADC_Initialize(5,1024);
	DIO_SetPinDirection(BOT1_PORT,BOT1_PIN,DIO_INPUT); //push button 
	Timer0_OVF_WithInterrupt_Initialize();
	
	uart_status UART_State= UART_Initialize_WithoutInterrupt(UART_9600,Synchronous, Disable , Bits_8, Bit_1);
	if(UART_State==UART_NOK){
		return 0;
	}

	External_Interrupt0_Initalize(INT0_RISING);
	

	
	// Read initial state from EEPROM
	uint8_t x= Read_E2PROM_State();
	if (x==0)
	{
		DC_Start(DC_fan1,DC_CW);
	}
	_delay_ms(10);

	/*	Main	Code	*/
    while(1)
    {	
		temperature=Read_TEMP_SENSOR();
		
		/* Send the message (Temperature)	*/
		UART_Transmit_State(temperature,temp_counter,&buttonPressed);
		
		/*
		//Recieve the message (Speed)	
		UART_Receive_Speed(&Speed_Scale);
		*/
		
		handle_event(temperature,&temp_counter,DC_fan1,Speed_Scale,&currentState,&reset);
		
		//check if need reset
		if(reset==1){
			//Watch dog
			WDT_ON();
		}
		
	}
}

/*	Interrupt Service Routine for INT0 (bot1)	 */
ISR(INT0_vect)
{
	bot1_intur++;
	buttonPressed = 1;		/* Set the flag */
	_delay_ms(50);  	/* Software debouncing control delay */
}

ISR(TIMER0_OVF_vect){
	
	overflow_count++;
	if (overflow_count >= 16) {
		overflow_count = 0;

		// check the temperature
		if(Read_TEMP_SENSOR()>=50){
			temp_counter++;
		}
	}

}