/*
 * ADC_Private.h
 *
 * Created: 10/7/2023 12:09:18 PM
 *  Author: oraga
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "ADC_Configuration.h"

void ADC_Initialize(adc_vref voltage , adc_prescaler prescaler);
uint16_t ADC_Read(adc_channel channel);




#endif /* ADC_PRIVATE_H_ */