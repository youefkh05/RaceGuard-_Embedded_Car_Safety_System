#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
#include "TWI_CONFIG.h"
/* Error Status fot TWI */

#define	NoError                             0
#define	StartConditionErr                   1
#define	RepeatedStartError                   2
#define	SlaveAddressWithWriteErr             3
#define SlaveAddressWithReadErr               4
#define MasterWriteByteErr                   5
#define MasterReadByteErr                    6
#define SlaveWriteByteErr                    7
#define SlaveReadByteErr                     8

void TWI_voidInitMaster(uint8_t Copy_UINT8Address);
void TWI_voidInitSlave(uint8_t Copy_UINT8Address);
uint8_t TWI_SendStartCondition(void);
uint8_t TWI_SendRepeatedStart(void);
uint8_t TWI_SendSlaveAddressWithWrite(uint8_t Copy_UINT8SlaveAddress);
uint8_t TWI_SendSlaveAddressWithRead(uint8_t Copy_UINT8SlaveAddress);
uint8_t TWI_MasterWriteDataByte(uint8_t Copy_UINT8DataByte);
uint8_t TWI_MasterReadDataByte(uint8_t* Copy_pUINT8DataByte);
uint8_t TWI_SlaveReadDataByte(uint8_t* Copy_pUINT8DataByte);
uint8_t TWI_SlaveWriteDataByte(uint8_t Copy_UINT8DataByte);
void TWI_SendStopCondition(void);


#endif
