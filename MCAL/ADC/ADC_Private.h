/*
 * ADC_Private.h
 *
 *  Created on: Aug 11, 2024
 *      Author: Abdelrahman Nasr
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define RIGHT_ADJUST 	0
#define LEFT_ADJUST 	1
#define HL_ADJUST   	2


// SELECTION BIT MASK for refrence - prescaler - channel - SFIOR
#define REF_SEL_BIT_MASK   0b00111111
#define PRES_SEL_BIT_MASK  0b11111000
#define CHANNEL_SEL_BIT_MASK 0b11100000


// difination references

#define AREF 		0b00000000
#define AVCC 		0b01000000
#define INTERNAL_2_56V 0b11000000
//#define INTERNAL_2_56V  0b11000000


//difination prescaler



#define PRE_DIV_BY_2  0b00000000
#define PRE_DIV_BY_4  0b00000010
#define PRE_DIV_BY_8  0b00000011
#define PRE_DIV_BY_16 0b00000100
#define PRE_DIV_BY_32 0b00000101
#define PRE_DIV_BY_64 0b00000110
#define PRE_DIV_BY_128 0b00000111




#define SFIOR_FREE_RUNNING 0b00000000



#define ADMUX *((volatile u8 *) 0x27 )

#define ADMUX_MUX0 0
#define ADMUX_MUX1 1
#define ADMUX_MUX2 2
#define ADMUX_MUX3 3
#define ADMUX_MUX4 4
#define ADMUX_ADLAR 5
#define ADMUX_REFS0 6
#define ADMUX_REFS1 7


//ADCSRA
#define ADCSRA *((volatile u8 *) 0x26 )

#define ADCSRA_ADPS0	0
#define ADCSRA_ADPS1	1
#define ADCSRA_ADPS2	2
#define ADCSRA_ADIE		3
#define ADCSRA_ADIF		4
#define ADCSRA_ADATE	5
#define ADCSRA_ADSC		6
#define ADCSRA_ADEN		7

#define ADCH *((volatile u8 *) 0x25 )

#define ADCL *((volatile u8 *) 0x24 )


#define ADCHL *((volatile u16 *) 0x24 )


#define SREG *( (volatile u8*) 0x5f) //from datasheet

#define SREG_I 7 //I BIT NUMBER FROM DATASHEET


#define SFIOR *((volatile u8 *) 0x50)
#define SFIOR_ADTS2 7
#define SFIOR_ADTS1 6
#define SFIOR_ADTS0 5





#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
