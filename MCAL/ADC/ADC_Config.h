/*
 * ADC_Config.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Abdelrahman Nasr
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/*
 * * option
 * LEFT_ADJUST
 * RIGHT_ADJUST
 * HL_ADJUST
 * /
 */

#define ADC_ADJUST_RESULT  RIGHT_ADJUST

/*
 * option
 * AREF
 * AVCC
 * INTERNAL_2.56
 * */

#define ADC_REFRENCE_SELECTION  INTERNAL_2_56


/**
 * PRESCALER _Option
 * PRE_DIV_BY_2
 * PRE_DIV_BY_4
 * PRE_DIV_BY_8
 */



#define ADC_PRESCALER_VALUE PRE_DIV_BY_128


/*option Enable - DISABLE */

#define ADC_ENABLE ENABLE


#endif /* MCAL_ADC_ADC_CONFIG_H_ */
