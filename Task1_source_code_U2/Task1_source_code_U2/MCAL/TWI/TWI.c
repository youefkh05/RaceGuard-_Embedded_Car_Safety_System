

#include "TWI_PRIVATE.h"
#include "TWI_INTERFACE.h"





void TWI_voidInitMaster(uint8_t Copy_UINT8Address)
{

	/*Set SCL frequency to 400kHz, with 8Mhz system frequency*/
	/*1- Set TWBR to 2 => [0:255] */

	TWBR= (uint8_t) (((F_CPU/SCL_Clock)-16) / (2*TWI_PRESCALLER));

	/* Set the prescaler */
	/*2- Clear the prescaler bits (TWPS)*/
	if (TWI_PRESCALLER==PRESCALLER_BY_1)
	{
		TWSR=0;
	}
	else if (TWI_PRESCALLER==PRESCALLER_BY_4)
	{
		TWSR=1;
	}
	else if (TWI_PRESCALLER==PRESCALLER_BY_16)
	{
		TWSR=2;
	}
	else if (TWI_PRESCALLER==PRESCALLER_BY_64)
	{
		TWSR=3;
	}

	/*Check if the master node will be addressed & set the Master Address */
	if(Copy_UINT8Address != 0)
	{
		/*Set the required address in the 7 MSB of TWAR*/
		TWAR = Copy_UINT8Address<<1;
	}
	else
	{
		/*Do nothing*/
	}

	/************** Enable *******************/

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI Peripheral*/
	SET_BIT(TWCR,TWCR_TWEN);
}


void TWI_voidInitSlave(uint8_t Copy_UINT8Address)
{
	/*Set the slave address*/
	TWAR = Copy_UINT8Address<<1;

	/************** Enable *******************/

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}


uint8_t TWI_SendStartCondition(void)
{
	uint8_t Local_Error= NoError;


	/*Send start condition*/
	SET_BIT(TWCR, TWCR_TWSTA);
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*
	Hint : we could use 
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	 */

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status (Bit Masking) */
	if((TWSR & 0xF8) != START_ACK )
	{
		Local_Error = StartConditionErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
uint8_t TWI_SendRepeatedStart(void)
{
	uint8_t Local_Error= NoError;

	/*Send start condition*/
	SET_BIT(TWCR, TWCR_TWSTA);
	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);
	/*
	Hint : we could use 
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	 */


	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != REP_START_ACK )
	{
		Local_Error = RepeatedStartError;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
uint8_t TWI_SendSlaveAddressWithWrite(uint8_t Copy_UINT8SlaveAddress)
{
	uint8_t Local_Error= NoError;

	/*send the 7bit slave address to the bus*/
	TWDR = (Copy_UINT8SlaveAddress<<1) ;
	/*set the write request in the LSB in the data register*/
	CLR_BIT(TWDR,0);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK )
	{
		Local_Error = SlaveAddressWithWriteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
uint8_t TWI_SendSlaveAddressWithRead(uint8_t Copy_UINT8SlaveAddress)
{
	uint8_t Local_Error= NoError;

	/*send the 7bit slave address to the bus*/
	TWDR = Copy_UINT8SlaveAddress <<1;
	/*set the read request in the LSB in the data register*/
	SET_BIT(TWDR,0);

	/*Clear the start condition bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK )
	{
		Local_Error = SlaveAddressWithReadErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
uint8_t TWI_MasterWriteDataByte(uint8_t Copy_UINT8DataByte)
{
	uint8_t Local_Error= NoError;

	/*Write the data byte on the bus*/
	TWDR = Copy_UINT8DataByte;

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  MSTR_WR_BYTE_ACK)
	{
		Local_Error = MasterWriteByteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
uint8_t TWI_MasterReadDataByte(uint8_t* Copy_pUINT8DataByte)
{
	uint8_t Local_Error= NoError;

	/*Clear the interrupt flag to allow the slave send the data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  MSTR_RD_BYTE_WITH_ACK)
	{
		Local_Error = MasterReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_pUINT8DataByte = TWDR;
	}

	return Local_Error;
}
uint8_t TWI_SlaveReadDataByte(uint8_t* Copy_pUINT8DataByte)
{
	uint8_t Local_Error= NoError;

	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  SLAVE_ADD_RCVD_WR_REQ)
	{
		Local_Error = SlaveReadByteErr;
	}

	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);
	/*Check the operation status*/
	if((TWSR & 0xF8) !=  SLAVE_DATA_RECEIVED)
	{
		Local_Error = SlaveReadByteErr;
	}
	else
	{
		/*Read the received data*/
		*Copy_pUINT8DataByte = TWDR;
	}

	return Local_Error;
}
uint8_t TWI_SlaveWriteDataByte(uint8_t Copy_UINT8DataByte)
{
	uint8_t Local_Error= NoError;

	/*Write the data byte on the bus*/
	TWDR = Copy_UINT8DataByte;

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised*/
	while((GET_BIT(TWCR,TWCR_TWINT))==0);

	/*Check the operation status*/
	if((TWSR & 0xF8) !=  SLAVE_BYTE_TRANSMITTED)
	{
		Local_Error = SlaveWriteByteErr;
	}
	else
	{
		/*Do nothing*/
	}

	return Local_Error;
}
void TWI_SendStopCondition(void)
{
	/*Sent a stop condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear the interrupt flag to start the previous operation*/
	SET_BIT(TWCR,TWCR_TWINT);

}