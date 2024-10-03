/*
 * LM35_TMP_Sensor_Interface.c
 *
 * Created: 8/12/2024 6:19:25 PM
 *  Author: youefkh05
 */ 

#include "LM35_TMP_Sensor_Private.h"

void Initialize_TEMP_SENSOR(void)
{
	DIO_SetPinDirection(TEMP_SEN_PORT, TEMP_SEN_PIN, DIO_OUTPUT);
}

temp Read_TEMP_SENSOR(void){
	uint16_t temp_volt=ADC_Read(TEMP_SEN_PIN);
	temp temp_read = temp_volt*500.0/1024.0 ;
	return temp_read;
}