/*
 * ADC_Program.c
 *
 *  Created on: Aug 11, 2024
 *      Author: Abdelrahman Nasr
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"


void MADC_VoidInit(void)
{
	// ENABLE ADC

	// enable auto trigger
	//SET_BIT(ADCSRA,ADCSRA_ADATE);

	// slect ref

	//#if ADC_REFRENCE_SELECTION == AREF
		ADMUX &= REF_SEL_BIT_MASK;
		ADMUX |= 0b11000000;//ADC_REFRENCE_SELECTION
	//#endif



	// prescaller
	/*check prescaler */

	//#if ADC_PRESCALER_VALUE == PRE_DIV_BY_128
		ADCSRA &= PRES_SEL_BIT_MASK;
		ADCSRA |= ADC_PRESCALER_VALUE;
	//#endif

	//ADC_ADJUST
	// RIGHT ADJUST
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);


	//#if ADC_ENABLE == ENABLE
		SET_BIT(ADCSRA,ADCSRA_ADEN);
	//#elif   ADC_ENABLE == DISABLE
		//CLEAR_BIT(ADCSRA,ADCSRA_ADEN);
	//#endif


}

u16 MADC_u8StartConversion(u8 Copy_u8ChannelNum)
{

		u16 Local_u8DigitalValue;
	    /*Set The Channel Of ADC*/
	    ADMUX &= CHANNEL_SEL_BIT_MASK;
	    ADMUX |= Copy_u8ChannelNum;

	    /*Start The ADC To Convert The Input Analog Signal*/
	    SET_BIT(ADCSRA, ADCSRA_ADSC);
	    /*Polling (busy wait) till the flag is raised*/
	    /*NOT RECOMMENDED AT ALL*/
	    while(!GET_BIT(ADCSRA, ADCSRA_ADIF));
	    /*Clear The Flag*/
	    SET_BIT(ADCSRA, ADCSRA_ADIF);
///*
//	    /*Check For Left or Right Adjust*/
//	    #if ADC_ADJUST_RESULT == LEFT_ADJUST
//	        Local_u8DigitalValue =  ADCH;
//	    #elif ADC_ADJUST_RESULT == RIGHT_ADJUST
//	        Local_u8DigitalValue =  ADCL;
//	    #endif
//*/

	    Local_u8DigitalValue = ADCHL;
	    /*Return The Digital Value*/
	    return Local_u8DigitalValue;
}
