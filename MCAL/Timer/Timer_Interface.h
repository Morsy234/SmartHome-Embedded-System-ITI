/*
 * Timer0_Interface.h
 *
 *  Created on: Aug 5, 2024
 *      Author: M
 */

#ifndef MCAL_TIMERS_TIMER0_INTERFACE_H_
#define MCAL_TIMERS_TIMER0_INTERFACE_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/*******************TIMRR0***************/

#define		TIMER0_SCALER_1     	 1
#define		TIMER0_SCALER_8    		 2
#define	    TIMER0_SCALER_64 		 3
#define 	TIMER0_SCALER_256        4
#define 	TIMER0_SCALER_1024       5
#define 	EXTERNALl_FALLING        6
#define 	EXTERNAL_RISING          7


#define		TIMER0_NORMAL_MODE        0
#define		TIMER0_PHASECORRECT_MODE  1
#define		TIMER0_CTC_MODE           2
#define		TIMER0_FASTPWM_MODE       3

// pwm moooooood
#define disconnected                  0
#define nin_inverting                 2
#define inverting                     3

void TIMER0_init(void);

void TIMER0_Start(void);

void TIMER0_Stop(void);

void TIMER0_Preload(u8 preload);

void TIMER0_IntrrupetEnable_OV();


void TIMER0_IntrrupetDisable_OV();


void TIMER0_IntrrupetEnable_OC();
void TIMER0_IntrrupetDisable_OC();

void TIMER0_OC_Value(u8 value);//20


void FAST_PWM_MODE_0(void);


/*******************TIMRR1***************/



#define 	TIMER1_SCALER_1     0
#define		TIMER1_SCALER_8     1
#define		TIMER1_SCALER_64    2
#define		TIMER1_SCALER_256   3
#define		TIMER1_SCALER_1024  4
#define		EXTERNAL0_FALLING   5
#define		EXTERNAL0_RISING    6




#define TIMER1_NORMAL_MODE            0
#define	TIMER1_CTC_ICR_TOP_MODE       1
#define	TIMER1_CTC_OCRA_TOP_MODE      2
#define	TIMER1_FASTPWM_ICR_TOP_MODE   3
#define	TIMER1_FASTPWM_OCRA_TOP_MODE  4


#define	OCRA1_DISCONNECTED   0
#define	RESERVED           1
#define	ORA1_NON_INVERTING  2
#define OCA1_INVERTING      3



#define	OCRB1_DISCONNECTED   0
#define	RESERVED           1
#define	ORB1_NON_INVERTING  2
#define OCB1_INVERTING      3



#define ICU_Edge_type_RISING     0
#define ICU_Edge_type_FALLING    1

// pwm moooooood
#define disconnected                  0
#define nin_inverting                 2
#define inverting                     3




void vTIMER1_INIT(void);


void vTIMER1_START(void);

void vTIMER1_STOP(void);

void vTIMER1_preload(u8 preload);

void Timer1_OCRA1Mode(u8 oc1a_mode);

void Timer1_OCRB1Mode(u8 oc1b_mode);

void vTIMER1_Compare_OCR1A(u16 OCRA);

void vTIMER1_Compare_OCRB1(u16 OCRB);

void vTIMER1_ICR1(u16 ICR);

void Timer1_InputCaptureEdge(u8 ICU_Edge_type_edge);


void Timer1_ICR_InterruptEnable(void);

void Timer1_ICR_InterruptDisable(void);

void Timer1_OVF_InterruptEnable(void);

void Timer1_OVF_InterruptDisable(void);

void Timer1_OCA_InterruptEnable(void);

void Timer1_OCA_InterruptDisable(void);

void Timer1_OCB_InterruptEnable(void);

void Timer1_OCB_InterruptDisable(void);

/*******************TIMRR2***************/





/*Timers OCx Pin Options*/
#define 	TIMER_OC_DISCONNECTED		0
#define 	TIMER_OC_TOGGLE				1
#define 	TIMER_OC_NON_INVERTING		2
#define 	TIMER_OC_INVERTING			3



/* Timer2 Mode Options */
#define TIMER2_NORMAL_MODE                        0
#define TIMER2_PWM_PHASE_CORRECT_MODE             1
#define TIMER2_CTC_MODE                           2
#define TIMER2_FASTPWM_MODE                       3
// Timer2 Prescalers
#define TIMER2_SCALER_1 1
#define TIMER2_SCALER_8 2
#define TIMER2_SCALER_32 3
#define TIMER2_SCALER_64 4
#define TIMER2_SCALER_128 5
#define TIMER2_SCALER_256 6
#define TIMER2_SCALER_1024 7

void vTimer2_Init(void);
void vTimer2_Start(void);
void vTimer2_Stop(void);
void vTimer2_SetMode(u8 mode);
void vTimer2_OC2_SetMode(u8 mode);
void vTimer2_SetPreLoad(u8 value);
void vTimer2_SetOCRValue(u8 value);
void vTimer2_OVF_InterruptEnable(void);
void vTimer2_OVF_InterruptDisable(void);
void vTimer2_OCM_InterruptEnable(void);
void vTimer2_OCM_InterruptDisable(void);
void vTimer2_PrescalerSelect(u8 prescaler);

#endif /* MCAL_TIMERS_TIMER0_INTERFACE_H_ */
