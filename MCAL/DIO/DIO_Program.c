/*
 * DIO_Program.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Ahmed Saber
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Config.h"
#include "DIO_Private.h"

/**
 * @brief Sets the direction (input or output) for a specified pin on a given port.
 *
 * @param PORT_ID The port ID to configure. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param PIN_ID The pin ID within the specified port (0-7).
 * @param Direction The direction to set for the pin. Can be OUTPUT or INPUT.
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - PIN_ID: The pin number to configure (0-7).
 *   - Direction: The direction to set (OUTPUT or INPUT).
 * @param parameters_out None.
 * @return None.
 */
void vSet_Pin_Direction(u8 PORT_ID, u8 PIN_ID, u8 Direction)
{
    switch(Direction)
    {
        case OUTPUT:
            switch(PORT_ID)
            {
                case PORT_A: SET_BIT(DDRA, PIN_ID); break;
                case PORT_B: SET_BIT(DDRB, PIN_ID); break;
                case PORT_C: SET_BIT(DDRC, PIN_ID); break;
                case PORT_D: SET_BIT(DDRD, PIN_ID); break;
            }
            break;

        case INPUT:
            switch(PORT_ID)
            {
                case PORT_A: CLEAR_BIT(DDRA, PIN_ID); break;
                case PORT_B: CLEAR_BIT(DDRB, PIN_ID); break;
                case PORT_C: CLEAR_BIT(DDRC, PIN_ID); break;
                case PORT_D: CLEAR_BIT(DDRD, PIN_ID); break;
            }
            break;
    }
}

/**
 * @brief Sets the output value (high or low) for a specified pin on a given port.
 *
 * @param PORT_ID The port ID to configure. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param PIN_ID The pin ID within the specified port (0-7).
 * @param Value The value to set for the pin. Can be HIGH or LOW.
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - PIN_ID: The pin number to configure (0-7).
 *   - Value: The value to set (HIGH or LOW).
 * @param parameters_out None.
 * @return None.
 */
void vSet_Pin_OUTPUTvalue(u8 PORT_ID, u8 PIN_ID, u8 Value)
{
    switch(Value)
    {
        case HIGH:
            switch(PORT_ID)
            {
                case PORT_A: SET_BIT(PORTA, PIN_ID); break;
                case PORT_B: SET_BIT(PORTB, PIN_ID); break;
                case PORT_C: SET_BIT(PORTC, PIN_ID); break;
                case PORT_D: SET_BIT(PORTD, PIN_ID); break;
            }
            break;

        case LOW:
            switch(PORT_ID)
            {
                case PORT_A: CLEAR_BIT(PORTA, PIN_ID); break;
                case PORT_B: CLEAR_BIT(PORTB, PIN_ID); break;
                case PORT_C: CLEAR_BIT(PORTC, PIN_ID); break;
                case PORT_D: CLEAR_BIT(PORTD, PIN_ID); break;
            }
            break;
    }
}

/**
 * @brief Toggles the state (high or low) of a specified pin on a given port.
 *
 * @param PORT_ID The port ID to configure. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param PIN_ID The pin ID within the specified port (0-7).
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - PIN_ID: The pin number to toggle (0-7).
 * @param parameters_out None.
 * @return None.
 */
void vTOGGLE_Pin(u8 PORT_ID, u8 PIN_ID)
{
    switch(PORT_ID)
    {
        case PORT_A: TOG_BIT(PORTA, PIN_ID); break;
        case PORT_B: TOG_BIT(PORTB, PIN_ID); break;
        case PORT_C: TOG_BIT(PORTC, PIN_ID); break;
        case PORT_D: TOG_BIT(PORTD, PIN_ID); break;
    }
}

/**
 * @brief Sets the direction (input or output) for all pins on a specified port.
 *
 * @param PORT_ID The port ID to configure. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param Direction The direction to set for all pins. Can be OUTPUT or INPUT.
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - Direction: The direction to set (OUTPUT or INPUT).
 * @param parameters_out None.
 * @return None.
 */
void vSet_Port_Direction(u8 PORT_ID, u8 Direction)
{
    switch(Direction)
    {
        case OUTPUT:
            switch(PORT_ID)
            {
                case PORT_A: DDRA = 0xff; break;
                case PORT_B: DDRB = 0xff; break;
                case PORT_C: DDRC = 0xff; break;
                case PORT_D: DDRD = 0xff; break;
            }
            break;

        case INPUT:
            switch(PORT_ID)
            {
                case PORT_A: DDRA = 0x00; break;
                case PORT_B: DDRB = 0x00; break;
                case PORT_C: DDRC = 0x00; break;
                case PORT_D: DDRD = 0x00; break;
            }
            break;
    }
}

/**
 * @brief Sets the output value (high or low) for all pins on a specified port.
 *
 * @param PORT_ID The port ID to configure. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param Value The value to set for all pins. Can be 0 (low) or 255 (high).
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - Value: The value to set for the port (0-255).
 * @param parameters_out None.
 * @return None.
 */
void vSet_Port_OUTPUTvalue(u8 PORT_ID, u8 Value)
{
    switch(PORT_ID)
    {
        case PORT_A: PORTA = Value; break;
        case PORT_B: PORTB = Value; break;
        case PORT_C: PORTC = Value; break;
        case PORT_D: PORTD = Value; break;
    }
}

/**
 * @brief Reads and returns the value of a specified pin on a given port.
 *
 * @param PORT_ID The port ID to read from. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param PIN_ID The pin ID within the specified port (0-7).
 * @param parameters_in
 *   - PORT_ID: The port to read from (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - PIN_ID: The pin number to read (0-7).
 * @param parameters_out The value of the pin (HIGH or LOW).
 * @return The value of the pin (0 or 1).
 */
u8 vGIT_PIN(u8 PORT_ID, u8 PIN_ID)
{
    u8 BIT = 0;
    switch(PORT_ID)
    {
        case PORT_A: BIT = GET_BIT(PINA, PIN_ID); break;
        case PORT_B: BIT = GET_BIT(PINB, PIN_ID); break;
        case PORT_C: BIT = GET_BIT(PINC, PIN_ID); break;
        case PORT_D: BIT = GET_BIT(PIND, PIN_ID); break;
    }
    return BIT;
}

/**
 * @brief Sets an internal pull-up resistor on a specified pin of a given port.
 *
 * @param PORT_ID The port ID where the pin is located. Can be PORT_A, PORT_B, PORT_C, or PORT_D.
 * @param PIN_ID The pin ID to enable the pull-up resistor (0-7).
 * @param parameters_in
 *   - PORT_ID: The port to configure (PORT_A, PORT_B, PORT_C, PORT_D).
 *   - PIN_ID: The pin number to enable the pull-up resistor (0-7).
 * @param parameters_out None.
 * @return None.
 */
void vSetInernalPullUp(u8 PORT_ID, u8 PIN_ID)
{
    vSet_Pin_OUTPUTvalue(PORT_ID, PIN_ID, HIGH);
}
