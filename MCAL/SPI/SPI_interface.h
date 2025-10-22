/*
 * SPI_interface.h
 *
 *  Created on: Aug 15, 2024
 *      Author: Nour
 */

#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

void MSPI_vMasterInit(void);
void MSPI_vSlaveInit(void);

u8 MSPI_u8Transcieve(u8 Copy_u8Data); //The parameter contains the data to be sent

void MSPI_voidTransmit(u8 Copy_u8Data);

void MSPI_voidReceive(u8 *Copy_pu8ReceivedData);


#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
