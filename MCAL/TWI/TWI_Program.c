/*
 * TWI_Program.c
 *
 *  Created on: Aug 18, 2024
 *      Author: Abdelrahman Nasr
 */

/* Include LIB Files */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/* Include driver Files */
#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "TWI_Config.h"

/* A function to Initialize Master */
void TWI_voidMasterInit (u8 Copy_u8SlaveAddress)
{
	/* Set Clock Frequency to 400kbps ( TWBR = 2, TWPS two Bits = 00 ) */
	TWBR = 2;
	CLEAR_BIT(TWSR, TWSR_TWPS0);
	CLEAR_BIT(TWSR, TWSR_TWPS1);

	/* Set address for master */
	if (Copy_u8SlaveAddress != 0)
	{
		/* Assign the required node address in the 7MSB in the register */
		TWAR = (Copy_u8SlaveAddress << 1);
	}

	/* Enable TWI */
	SET_BIT(TWCR, TWCR_TWEN);
}

/* A function to Initialize Slave */
void TWI_voidSlaveInit (u8 Copy_u8SlaveAddress)
{
	/* Assign the required node address in the 7MSB in the register */
	TWAR = Copy_u8SlaveAddress << 1;

	/* Enable TWI */
	SET_BIT(TWCR, TWCR_TWEN);
}

/* A function to send start condition */
TWI_ErrStatus TWI_SendStartCondition (void)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Send Start Condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != START_ACK)
	{
		Local_ErrStatus = StartConditionErr;
	}
	else
	{
		/* Do nothing */
	}

	return Local_ErrStatus;
}

/* A function to send repeated start */
TWI_ErrStatus TWI_SendRepeatedStart (void)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Send Start Condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != REP_START_ACK)
	{
		Local_ErrStatus = RepeatedStartConditionErr;
	}
	else
	{
		/* Do nothing */
	}

	return Local_ErrStatus;
}

/* A function to send slave address with write */
TWI_ErrStatus TWI_SendSlaveAddressWithWrite (u8 Copy_u8SlaveAddress)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Set the slave address in the 7 MSB in the data register */
	TWDR = (Copy_u8SlaveAddress << 1);

	/* Select Write */
	CLEAR_BIT(TWDR, TWDR_TWD0);

	/* Clear Start Condition bit */
	CLEAR_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrStatus = SlaveAddressWithWriteErr;
	}
	else
	{
		/* Do nothing */
	}

	return Local_ErrStatus;
}

/* A function to send slave address with read */
TWI_ErrStatus TWI_SendSlaveAddressWithRead (u8 Copy_u8SlaveAddress)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Set the slave address in the 7 MSB in the data register */
	TWDR = Copy_u8SlaveAddress << 1;

	/* Select Read */
	SET_BIT(TWDR, TWDR_TWD0);

	/* Clear Start Condition bit */
	CLEAR_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrStatus = SlaveAddressWithReadErr;
	}
	else
	{
		/* Do nothing */
	}

	return Local_ErrStatus;
}

/* A function to write data byte */
TWI_ErrStatus TWI_MasterWriteDataByte (u8 Copy_u8DataByte)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Write the data Byte */
	TWDR = Copy_u8DataByte;

	/* Clear the interrupt flag to start previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrStatus = MasterWriteByteErr;
	}
	else
	{
		/* Do nothing */
	}

	return Local_ErrStatus;
}

/* A function to read data byte */
TWI_ErrStatus TWI_MasterReadDataByte (u8 *Copy_pu8DataByte)
{
	/* Variable for Error Status */
	TWI_ErrStatus Local_ErrStatus = NoError;

	/* Enable Master generating acknowledge bit after receiving the data */
	CLEAR_BIT(TWCR, TWCR_TWEA);

	/* Clear the interrupt flag to start Slave Send data */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again and previous operation is complete */
	while ((GET_BIT(TWCR, TWCR_TWINT)) == 0);

	/* Check for the operation  */
	if ((TWSR & 0xF8) != MSTR_RD_BYTE_WITH_NACK)
	{
		Local_ErrStatus = MasterReadByteErr;
	}
	else
	{
		/* Read the received data */
		*Copy_pu8DataByte = TWDR;
	}

	return Local_ErrStatus;
}

/* A function to send stop condition */
void TWI_SendStopCondition (void)
{
	/* Generate stop condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTO);

	/* Clear the interrupt flag to start Slave Send data */
	SET_BIT(TWCR, TWCR_TWINT);
}
