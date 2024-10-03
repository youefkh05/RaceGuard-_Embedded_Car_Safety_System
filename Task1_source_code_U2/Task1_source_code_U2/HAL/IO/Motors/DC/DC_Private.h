/*
 * DC_Private.h
 *
 * Created: 8/12/2024 6:59:00 PM
 *  Author: youefkh05
 */ 


#ifndef DC_PRIVATE_H_
#define DC_PRIVATE_H_

#include "DC_Configurations.h"

void DC_Initialize(dc_motor motor);
void DC_Start(dc_motor motor, dc_motor_direction direction);
void DC_Stop(dc_motor motor);
void DC_Change_Speed(dc_motor motor,uint16_t speed);





#endif /* DC_PRIVATE_H_ */