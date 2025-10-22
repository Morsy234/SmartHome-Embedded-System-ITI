/*
 * Timer0_Program.c
 *
 *  Created on: Aug 5, 2024
 *      Author: M
 */



#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMER_Config.h"
#include "TIMER_Interface.h"
#include "TIMER_Private.h"


/**************TIMER0***********************/
/**
 * @brief Initializes TIMER0 with the selected mode and preload value.
 *
 * @param None.
 * @param parameters_in The mode and initial value settings for TIMER0.
 * @param parameters_out None.
 * @return None.
 */

void TIMER0_init(void){
	/*MODE SELECT*/
	switch(TIMER0_Mode){
	case TIMER0_NORMAL_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		/*ENABLE OVERFLOW INTRRUPET*/
		TIMER0_IntrrupetEnable_OV();

		break;
	case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		break;
	case TIMER0_CTC_MODE:
		CLEAR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		/*ENABLE COMPARE MATCH INTRRUPET*/
		TIMER0_IntrrupetEnable_OC();
		break;
	case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		break;
	default:
		break;
	}


	/*SET INTI VALUE*/
	TIMER0_Preload(TIMER0_INITIAL_VALUE);
}

/**
 * @brief Starts TIMER0 with the selected prescaler.
 *
 * @param None.
 * @param parameters_in The prescaler setting for TIMER0.
 * @param parameters_out None.
 * @return None.
 */

void TIMER0_Start(void){
	/*SELECT PRESCALER*/
	switch(TIMER0_Prescaler){
	case TIMER0_SCALER_1:
		SET_BIT(TCCR0,CS00);
		break;
	case TIMER0_SCALER_1024:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS02);
		break;
	case TIMER0_SCALER_256:
		SET_BIT(TCCR0,CS02);
		break;
	case TIMER0_SCALER_64:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		break;
	case TIMER0_SCALER_8:
		SET_BIT(TCCR0,CS01);
		break;
	case EXTERNAL_RISING:
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
	case EXTERNALl_FALLING:
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
	default:
		break;

	}
}

/**
 * @brief Configures the PWM mode for TIMER0 in Fast PWM mode.
 *
 * @param None.
 * @param parameters_in The PWM mode settings for TIMER0.
 * @param parameters_out None.
 * @return None.
 */

void FAST_PWM_MODE_0(void)
{
	switch(PWM_MODE_0)
	{
	case disconnected:
		CLEAR_BIT(TCCR0 , COM00);
		CLEAR_BIT(TCCR0 , COM01);
		break;
	case nin_inverting:
		CLEAR_BIT(TCCR0 , COM00);
		SET_BIT(TCCR0 , COM01);
		break;
	case inverting:
		SET_BIT(TCCR0 , COM00);
		SET_BIT(TCCR0 , COM01);
		break;

	}
}
/**
 * @brief Enables TIMER0 overflow interrupt.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void TIMER0_IntrrupetEnable_OV(){
	SET_BIT(TIMSK,TOIE0);
}
/**
 * @brief Disables TIMER0 overflow interrupt.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void TIMER0_IntrrupetDisable_OV(){
	CLEAR_BIT(TIMSK,TOIE0);
}

/**
 * @brief Enables TIMER0 compare match interrupt.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */

void TIMER0_IntrrupetEnable_OC(){
	SET_BIT(TIMSK,OCIE0);
}
/**
 * @brief Disables TIMER0 compare match interrupt.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void TIMER0_IntrrupetDisable_OC(){
	CLEAR_BIT(TIMSK,OCIE0);
}


/**
 * @brief Stops TIMER0.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */

void TIMER0_Stop(void){
	TCCR0=0X00;
}

/**
 * @brief Sets the preload value for TIMER0.
 *
 * @param preload The value to preload the TIMER0 counter with.
 * @param parameters_in The preload value.
 * @param parameters_out None.
 * @return None.
 */
void TIMER0_Preload(u8 preload){
	TCNT0=preload;
}

/**
 * @brief Sets the output compare value for TIMER0.
 *
 * @param value The value to set for the output compare register.
 * @param parameters_in The output compare value.
 * @param parameters_out None.
 * @return None.
 */
void TIMER0_OC_Value(u8 value){
	OCR0=value;
}





/***********************************************TIMER1*******************/
/**
 * @brief Initializes TIMER1 with the selected mode.
 *
 * @param None.
 * @param parameters_in The mode settings for TIMER1.
 * @param parameters_out None.
 * @return None.
 */

void vTIMER1_INIT(void)
{

#if TIMER1_MODE==TIMER1_NORMAL_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	CLEAR_BIT(TCCR1B,WGM12);
	CLEAR_BIT(TCCR1B,WGM13);
#elif TIMER1_MODE==TIMER1_CTC_ICR_TOP_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);

#elif TIMER1_MODE==TIMER1_CTC_OCRA_TOP_MODE

	CLEAR_BIT(TCCR1A,WGM10);
	CLEAR_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLEAR_BIT(TCCR1B,WGM13);
#elif  TIMER1_MODE==TIMER1_FASTPWM_ICR_TOP_MODE
	CLEAR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#elif  TIMER1_MODE==TIMER1_FASTPWM_OCRA_TOP_MODE
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
#endif


}
/**
 * @brief Configures the mode for output compare channel A of TIMER1.
 *
 * @param oc1a_mode The mode to set for output compare channel A.
 * @param parameters_in The output compare mode for channel A.
 * @param parameters_out None.
 * @return None.
 */

void Timer1_OCRA1Mode(u8 oc1a_mode)
{
	switch (oc1a_mode)
	{
	case OCRA1_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1A0);
		CLEAR_BIT(TCCR1A,COM1A1);
		break;

	case ORA1_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	case OCA1_INVERTING:
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
		break;
	}
}
/**
 * @brief Configures the mode for output compare channel B of TIMER1.
 *
 * @param oc1b_mode The mode to set for output compare channel B.
 * @param parameters_in The output compare mode for channel B.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OCRB1Mode(u8 oc1b_mode)
{
	switch (oc1b_mode)
	{
	case OCRB1_DISCONNECTED:
		CLEAR_BIT(TCCR1A,COM1B0);
		CLEAR_BIT(TCCR1A,COM1B1);
		break;

	case ORB1_NON_INVERTING:
		CLEAR_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	case OCB1_INVERTING:
		SET_BIT(TCCR1A,COM1B0);
		SET_BIT(TCCR1A,COM1B1);
		break;
	}
}
/**
 * @brief Starts TIMER1 with the selected prescaler.
 *
 * @param None.
 * @param parameters_in The prescaler setting for TIMER1.
 * @param parameters_out None.
 * @return None.
 */

void vTIMER1_START(void)
{
	TCCR1B=TCCR1B&0b11111000;
	TCCR1B=TCCR1B|TIMER1_PRESCALLER;
}
/**
 * @brief Stops TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void vTIMER1_STOP(void)
{
	CLEAR_BIT(TCCR1B,0);
	CLEAR_BIT(TCCR1B,1);
	CLEAR_BIT(TCCR1B,2);
}
/**
 * @brief Sets the preload value for TIMER1.
 *
 * @param preload The value to preload the TIMER1 counter with.
 * @param parameters_in The preload value.
 * @param parameters_out None.
 * @return None.
 */
void vTIMER1_preload(u8 preload)
{
	TCNT1=preload;
}
/**
 * @brief Sets the output compare value for channel A of TIMER1.
 *
 * @param OCRA The value to set for output compare register A.
 * @param parameters_in The output compare value for channel A.
 * @param parameters_out None.
 * @return None.
 */
void vTIMER1_Compare_OCR1A(u16 OCRA)
{
	OCR1A=OCRA;
}
/**
 * @brief Sets the output compare value for channel B of TIMER1.
 *
 * @param OCRB The value to set for output compare register B.
 * @param parameters_in The output compare value for channel B.
 * @param parameters_out None.
 * @return None.
 */
void vTIMER1_Compare_OCRB1(u16 OCRB)
{
	OCR1B=OCRB;
}
/**
 * @brief Sets the input capture register value for TIMER1.
 *
 * @param ICR The value to set for the input capture register.
 * @param parameters_in The input capture value.
 * @param parameters_out None.
 * @return None.
 */
void vTIMER1_ICR1(u16 ICR)
{
	ICR1=ICR;
}
/**
 * @brief Configures the input capture edge type for TIMER1.
 *
 * @param ICU_Edge_type_edge The edge type to configure (rising or falling).
 * @param parameters_in The edge type for input capture.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_InputCaptureEdge(u8 ICU_Edge_type_edge)
{
	if(ICU_Edge_type_edge==ICU_Edge_type_RISING)
		SET_BIT(TCCR1B,ICES1);

	else if(ICU_Edge_type_edge==ICU_Edge_type_RISING)
		CLEAR_BIT(TCCR1B,ICES1);
}
/**
 * @brief Enables input capture interrupt for TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */

void Timer1_ICR_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}

/**
 * @brief Disables input capture interrupt for TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_ICR_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TICIE1);
}

/**
 * @brief Enables overflow interrupt for TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE1);
}

/**
 * @brief Disables overflow interrupt for TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OVF_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TOIE1);
}

/**
 * @brief Enables output compare interrupt for channel A of TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1A);
}

/**
 * @brief Disables output compare interrupt for channel A of TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OCA_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, OCIE1A);
}

/**
 * @brief Enables output compare interrupt for channel B of TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE1B);
}

/**
 * @brief Disables output compare interrupt for channel B of TIMER1.
 *
 * @param None.
 * @param parameters_in None.
 * @param parameters_out None.
 * @return None.
 */
void Timer1_OCB_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, OCIE1B);
}


/**********************************Timer 2**************************************/

// Timer2 Initialization
void vTIMER2_Init(void)
{
    /*1. Select Mode*/
    vTimer2_SetMode(TIMER2_MODE);

    /*2- Select OC2 Pin Mode*/
    vTimer2_OC2_SetMode(TIMER2_OC2_MODE);

    /*3- Set Pre-load "Initial Counting Value" Value*/
    vTimer2_SetPreLoad(TIMER2_INITIAL_VALUE);

    /*4- Set Compare Match Value*/
    vTimer2_SetOCRValue(TIMER2_OCR2_VALUE);

    /*5- Enable/ Disable OV Interrupt*/
    vTimer2_OVF_InterruptDisable();

    /*6- Enable/ Disable OC Interrupt*/
    vTimer2_OCM_InterruptDisable();
}

// Timer2 Start
void vTIMER2_Start(void)
{
    vTimer2_PrescalerSelect(TIMER2_PRESCALER);
}

// Timer2 Stop
void vTIMER2_Stop(void)
{
    CLEAR_BIT(TCCR2, CS20);
    CLEAR_BIT(TCCR2, CS21);
    CLEAR_BIT(TCCR2, CS22);
}

// Set Timer2 Pre-load
void vTimer2_SetPreLoad(u8 value)
{
    TCNT2 = value;
}

// Set Timer2 Compare Match Value
void vTimer2_SetOCRValue(u8 value)
{
    OCR2 = value;
}

// Set Timer2 Mode
void vTimer2_SetMode(u8 mode)
{
    switch (mode)
    {
    case TIMER2_NORMAL_MODE:
        CLEAR_BIT(TCCR2, WGM20);
        CLEAR_BIT(TCCR2, WGM21);
        break;

    case TIMER2_PWM_PHASE_CORRECT_MODE:
        SET_BIT(TCCR2, WGM20);
        CLEAR_BIT(TCCR2, WGM21);
        break;

    case TIMER2_CTC_MODE:
        CLEAR_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
        break;

    case TIMER2_FASTPWM_MODE:
        SET_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
        break;

    default:
        // Error handling
        break;
    }
}

// Set Timer2 OC2 Mode
void vTimer2_OC2_SetMode(u8 mode)
{
    switch (mode)
    {
    case TIMER_OC_DISCONNECTED:
        CLEAR_BIT(TCCR2, COM20);
        CLEAR_BIT(TCCR2, COM21);
        break;

    case TIMER_OC_TOGGLE:
        SET_BIT(TCCR2, COM20);
        CLEAR_BIT(TCCR2, COM21);
        break;

    case TIMER_OC_NON_INVERTING:
        CLEAR_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
        break;

    case TIMER_OC_INVERTING:
        SET_BIT(TCCR2, COM20);
        SET_BIT(TCCR2, COM21);
        break;

    default:
        // Error handling
        break;
    }
}

// Timer2 OVF Interrupt Enable
void vTimer2_OVF_InterruptEnable(void)
{
    SET_BIT(TIMSK, TOIE2);
}

// Timer2 OVF Interrupt Disable
void vTimer2_OVF_InterruptDisable(void)
{
    CLEAR_BIT(TIMSK, TOIE2);
}

// Timer2 OCM Interrupt Enable
void vTimer2_OCM_InterruptEnable(void)
{
    SET_BIT(TIMSK, OCIE2);
}

// Timer2 OCM Interrupt Disable
void vTimer2_OCM_InterruptDisable(void)
{
    CLEAR_BIT(TIMSK, OCIE2);
}

// Set Timer2 Prescaler
void vTimer2_PrescalerSelect(u8 prescaler)
{
    switch (prescaler)
    {
    case TIMER2_SCALER_1:
        SET_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_8:
        CLEAR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_32:
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        CLEAR_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_64:
        CLEAR_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_128:
        SET_BIT(TCCR2, CS20);
        CLEAR_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_256:
        CLEAR_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    case TIMER2_SCALER_1024:
        SET_BIT(TCCR2, CS20);
        SET_BIT(TCCR2, CS21);
        SET_BIT(TCCR2, CS22);
        break;
    default:
        // Error handling
        break;
    }
}
