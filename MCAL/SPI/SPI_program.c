/*

 * SPI_program.c
 *
 *  Created on: Aug 15, 2024
 *      Author: Nour
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_interface.h"


void MSPI_vMasterInit(void){
	//1- Data Order
	set_bit(SPCR, SPCR_DORD);

	//2- Master mode
	set_bit(SPCR, SPCR_MSTR);

	//3- Polarity
	clr_bit(SPCR, SPCR_CPOL);

	//4- Clock Phase Select
	clr_bit(SPCR, SPCR_CPHA);

	//5- Clock Frequency
	set_bit(SPCR, SPCR_SPR0);
	clr_bit(SPCR, SPCR_SPR1);
	clr_bit(SPSR, SPSR_SPI2X);

	//6- Disable SPI interrupt
	clr_bit(SPCR, SPCR_SPIE);

	//7-Enable SPI
	set_bit(SPCR, SPCR_SPE);
}
void MSPI_vSlaveInit(void){
	//1- Data Order
	set_bit(SPCR, SPCR_DORD);

	//2- Slave mode
	clr_bit(SPCR, SPCR_MSTR);

	//3- Polarity
	clr_bit(SPCR, SPCR_CPOL);

	//4- Clock Phase Select
	clr_bit(SPCR, SPCR_CPHA);

	//5- Clock Frequency
	set_bit(SPCR, SPCR_SPR0);
	clr_bit(SPCR, SPCR_SPR1);
	clr_bit(SPSR, SPSR_SPI2X);

	//6-Disable SPI interrupt
	clr_bit(SPCR, SPCR_SPIE);

	//7- Enable SPI
	set_bit(SPCR, SPCR_SPE);
}

void MSPI_voidTransmit(u8 Copy_u8Data){
	SPDR = Copy_u8Data;
	while(!get_bit(SPSR, SPSR_SPIF));


}

void MSPI_voidReceive(u8 *Copy_pu8ReceivedData){
	while(!get_bit(SPSR, SPSR_SPIF));
	*Copy_pu8ReceivedData = SPDR;
}


u8 MSPI_u8Transcieve(u8 Copy_u8Data){
	//The parameter contains the data to be sent
	SPDR = Copy_u8Data;

	while(!get_bit(SPSR, SPSR_SPIF));
	return SPDR;

}
