/*
 * TWI_Interface.h
 *
 *  Created on: Aug 18, 2024
 *      Author: Abdelrahman Nasr
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_



/* Enum to carry Error States */
typedef enum
{
	NoError,
	StartConditionErr,
	RepeatedStartConditionErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,

}TWI_ErrStatus;

/* A function to Initialize Master */
void TWI_voidMasterInit (u8 Copy_u8SlaveAddress);

/* A function to Initialize Slave */
void TWI_voidSlaveInit (u8 Copy_u8SlaveAddress);

/* A function to send start condition */
TWI_ErrStatus TWI_SendStartCondition (void);

/* A function to send repeated start */
TWI_ErrStatus TWI_SendRepeatedStart (void);

/* A function to send slave address with write */
TWI_ErrStatus TWI_SendSlaveAddressWithWrite (u8 Copy_u8SlaveAddress);

/* A function to send slave address with read */
TWI_ErrStatus TWI_SendSlaveAddressWithRead (u8 Copy_u8SlaveAddress);

/* A function to write data byte */
TWI_ErrStatus TWI_MasterWriteDataByte (u8 Copy_u8DataByte);

/* A function to read data byte */
TWI_ErrStatus TWI_MasterReadDataByte (u8 *Copy_pu8DataByte);

/* A function to send stop condition */
void TWI_SendStopCondition (void);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
