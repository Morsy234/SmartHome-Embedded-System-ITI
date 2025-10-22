/*
 * SERVO.c
 *
 *  Created on: Aug 16, 2024
 *      Author: M
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_Config.h"
#include "../../MCAL/GLOBAL_INT/GLOB_INT_Interface.h"
#include "../../MCAL/EXT_INT/EXT_INT_Interface.h"
#include "../../MCAL/TIMER/TIMER_Interface.h"
#include "../../MCAL/Timer/Timer_Config.h"
#include "SERVO.h"

#define F_CPU 8000000UL

void servo_angle(u8 angle)//0 ->180
{
	u16 val =  (((u32)1000*angle)/180)+1000; // 1000 ->2000
	vTIMER1_Compare_OCR1A(val);
}
void SERVO_app(){

	/*DIO INIT */
	vSet_Pin_Direction(PORT_D,PIN_5,OUTPUT);

	vTIMER1_INIT();
	vTIMER1_ICR1(20000);
	Timer1_OCRA1Mode(ORA1_NON_INVERTING);
	//vTIMER1_Compare_OCR1A(2000);//90
	//vTIMER1_START();
}
