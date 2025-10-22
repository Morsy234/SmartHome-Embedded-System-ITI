/*
 * LCD_Interface.h
 *
 *  Created on: Aug 1, 2024
 *      Author: Ahmed Saber
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

void vLCD_init(void);

void vLCD_sendCOMMAND(u8 command);

void vLCD_sendDATA(u8 data);

void vLCD_Send_String(u8 * str);

void CLCD_voidSendNumber(s32 cpy_u32Number);

void vLCD_Clear();

void vLCD_GO_TO(u8 line ,u8 position );
void vLCD_Convert_numTOchar(u16 num);
#endif /* HAL_LCD_LCD_INTERFACE_H_ */
