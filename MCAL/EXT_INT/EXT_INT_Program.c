/*
 * EXT_INT_Program.C
 *
 *  Created on: Aug 1, 2024
 *      Author: Ahmed Saber
 */
#include "EXT_INT_Interface.h"
#include "EXT_INT_Private.h"
#include "EXT_INT_Config.h"

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/**
 * @brief Enables the specified external interrupt source.
 *
 * @param source The external interrupt source to enable. Can be EXT_INT_0, EXT_INT_1, or EXT_INT_2.
 * @param parameters_in
 *   - EXT_INT_0: Enable External Interrupt 0.
 *   - EXT_INT_1: Enable External Interrupt 1.
 *   - EXT_INT_2: Enable External Interrupt 2.
 * @param parameters_out None.
 * @return None.
 */
void EXT_INT_Enable(EXT_INT_Sources source)
{
    switch(source)
    {
        case EXT_INT_0:
            SET_BIT(GICR, INT0_En_Bit);
            break;

        case EXT_INT_1:
            SET_BIT(GICR, INT1_En_Bit);
            break;

        case EXT_INT_2:
            SET_BIT(GICR, INT2_En_Bit);
            break;

        default:
            break;
            /*error handling*/
    }
}

/**
 * @brief Disables the specified external interrupt source.
 *
 * @param source The external interrupt source to disable. Can be EXT_INT_0, EXT_INT_1, or EXT_INT_2.
 * @param parameters_in
 *   - EXT_INT_0: Disable External Interrupt 0.
 *   - EXT_INT_1: Disable External Interrupt 1.
 *   - EXT_INT_2: Disable External Interrupt 2.
 * @param parameters_out None.
 * @return None.
 */
void EXT_INT_Disable(EXT_INT_Sources source)
{
    switch(source)
    {
        case EXT_INT_0:
            CLEAR_BIT(GICR, INT0_En_Bit);
            break;

        case EXT_INT_1:
            CLEAR_BIT(GICR, INT1_En_Bit);
            break;

        case EXT_INT_2:
            CLEAR_BIT(GICR, INT2_En_Bit);
            break;

        default:
            break;
            /*error handling*/
    }
}

/**
 * @brief Sets the trigger type for the specified external interrupt source.
 *
 * @param source The external interrupt source to configure. Can be EXT_INT_0, EXT_INT_1, or EXT_INT_2.
 * @param trigger The trigger type for the interrupt. Can be LOW_LEVEL, ANY_LOGICAL_CHANGE, FALLING, or RISING.
 * @param parameters_in
 *   - source: The external interrupt source (EXT_INT_0, EXT_INT_1, EXT_INT_2).
 *   - trigger: The type of edge or level that triggers the interrupt.
 * @param parameters_out None.
 * @return None.
 */
void EXT_INT_setTriggerType(EXT_INT_Sources source, EXT_INT_TriggerTypes trigger)
{
    switch(source)
    {
        case EXT_INT_0:
            switch(trigger)
            {
                case LOW_LEVEL:
                    CLEAR_BIT(MCUCR, ISC00);
                    CLEAR_BIT(MCUCR, ISC01);
                    break;

                case ANY_LOGICAL_CHANGE:
                    SET_BIT(MCUCR, ISC00);
                    CLEAR_BIT(MCUCR, ISC01);
                    break;

                case FALLING:
                    CLEAR_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
                    break;

                case RISING:
                    SET_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
                    break;

                default:
                    break;
                    /*error handling*/
            }
            break;

        case EXT_INT_1:
            switch(trigger)
            {
                case LOW_LEVEL:
                    CLEAR_BIT(MCUCR, ISC10);
                    CLEAR_BIT(MCUCR, ISC11);
                    break;

                case ANY_LOGICAL_CHANGE:
                    SET_BIT(MCUCR, ISC10);
                    CLEAR_BIT(MCUCR, ISC11);
                    break;

                case FALLING:
                    CLEAR_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
                    break;

                case RISING:
                    SET_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
                    break;

                default:
                    break;
                    /*error handling*/
            }
            break;

        case EXT_INT_2:
            switch(trigger)
            {
                case FALLING:
                    CLEAR_BIT(MCUCSR, ISC2);
                    break;

                case RISING:
                    SET_BIT(MCUCSR, ISC2);
                    break;

                default:
                    break;
                    /*error handling*/
            }
            break;

        default:
            break;
            /*error handling*/
    }
}
