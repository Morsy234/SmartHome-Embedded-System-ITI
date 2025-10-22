/*
 * Timers_Config.h
 *
 *  Created on: Aug 5, 2024
 *      Author: M
 */

#ifndef MCAL_TIMERS_TIMERS_CONFIG_H_
#define MCAL_TIMERS_TIMERS_CONFIG_H_

/****************TIMER0****************/

#define TIMER0_Prescaler     TIMER0_SCALER_256
#define TIMER0_Mode          TIMER0_CTC_MODE
#define TIMER0_INITIAL_VALUE			0

#define PWM_MODE_0       inverting



/*************TIMER1*****************/

#define TIMER1_PRESCALLER               TIMER1_SCALER_64

#define TIMER1_MODE                     TIMER1_FASTPWM_ICR_TOP_MODE

// Timer2 Mode
#define TIMER2_MODE 					 TIMER2_FASTPWM_MODE
#define TIMER2_OC2_MODE					 TIMER_OC_NON_INVERTING
#define TIMER2_INITIAL_VALUE					 0
#define TIMER2_OCR2_VALUE 						0
#define TIMER2_PRESCALER 				TIMER2_SCALER_64

#endif /* MCAL_TIMERS_TIMERS_CONFIG_H_ */
