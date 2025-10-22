/*
 * EEPROM_Interface.h
 *
 *  Created on: Aug 18, 2024
 *      Author: Abdelrahman Nasr
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_


/* A function to write a byte on the EEPROM */
void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

/* A function to read a byte on the EEPROM */
u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
