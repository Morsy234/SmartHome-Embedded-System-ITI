/*
 * Service.c
 *
 *  Created on: Aug 11, 2024
 *      Author: M
 */

#include <avr/interrupt.h>
#include <util/delay.h>

#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/DIO/DIO_Config.h"
#include "../MCAL/UART/UART_Int.h"
#include "../MCAL/UART/UART_Conf.h"
#include "../MCAL/TWI/TWI_Interface.h"
#include "../MCAL/Timer/Timer_Interface.h"
#include "../HAL/KEYPAD/KPD_Interface.h"



#include "../HAL/EEPROM/EEPROM_Config.h"
#include "../HAL/EEPROM/EEPROM_Interface.h"


#include "../HAL/LCD/LCD_Config.h"
#include "../HAL/LCD/LCD_Interface.h"

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"


#define F_CPU 8000000UL

#define PASSWORD_LENGTH 5
#define USERNAME_LENGTH 5
#define MAX_USERS 10
#define NUM_OF_TRIALS_ADDR 25

// Pins
#define BUZZER_PIN PIN_4
#define LIGHT_PIN PIN_5  // Assuming light is connected to PIN_5 of PORT_B

/**
 * @brief Initializes the system hardware.
 *
 * This function sets up the UART, LCD, servo motor, and light control pin.
 * It also resets the number of login trials stored in EEPROM.
 */
void app_init(void) {
	// Initialize TX (Transmit) and RX (Receive) for UART (Bluetooth)
	//vSet_Pin_Direction(PORT_D, PIN_0, INPUT);   // RXD as input
	//vSet_Pin_Direction(PORT_D, PIN_1, OUTPUT);  // TXD as output

	//MUART_voidInit(); // Initialize UART for communication
	vLCD_init(); // Initialize LCD display
	SERVO_app(); // Initialize servo application
	MADC_VoidInit();  // Initialize ADC
	vTIMER2_Init(); //initialize timer2



	// Set pin directions for various ports
	vSet_Pin_Direction(PORT_A, PIN_3, OUTPUT); // Set pin 3 of PORT_A as output (e.g., LED)
	vSet_Pin_Direction(PORT_A, PIN_4, OUTPUT); // Set pin 4 of PORT_A as output (e.g., Buzzer)
	vSet_Pin_Direction(PORT_A, PIN_7, INPUT);  // Set pin 7 of PORT_A as input (e.g., ADC for LM35)
	vSet_Pin_Direction(PORT_D, PIN_7, OUTPUT);  // Set pin 7 of PORT_D as output (e.g., FAN)
	vSet_Pin_Direction(PORT_C, PIN_5, OUTPUT);  // Set pin 5 of PORT_C as output (e.g., Temp warning LED)

	vSet_Pin_Direction(PORT_A, PIN_0, INPUT);  // Set pin 0 of PORT_A as input (e.g., ADC for LDR)
	vSet_Pin_Direction(PORT_C, PIN_2, OUTPUT); // ROOM1 LDR
	vSet_Pin_Direction(PORT_C, PIN_3, OUTPUT); // ROOM2 LDR
	vSet_Pin_Direction(PORT_C, PIN_4, OUTPUT); // ROOM3 LDR


	EEPROM_voidSendDataByte(NUM_OF_TRIALS_ADDR, 0);

	vKEYPAD_init();

}



/**
 * @brief Displays a welcome message on the LCD.
 *
 * This function clears the LCD and displays a welcome message for the user.
 */
void welcome_message(void) {
	vLCD_Clear();
	vLCD_Send_String("***Smart Home***");
	vLCD_GO_TO(2,0);
	vLCD_Send_String("    Welcome!");
}

/**
 * @brief Gets user input via Bluetooth.
 *
 * @param input Pointer to a buffer where the input will be stored.
 * @param length Maximum length of input to be read.
 * @return u8 The actual length of the input received.
 *
 * This function receives input from the user via Bluetooth and stores it in the provided buffer.
 * It displays '*' on the LCD for each character to maintain security.
 */
u8 get_input(u8* input, u8 length) {
    u8 cnt = 0;
    u8 key;

    while (cnt < length) {
        key = u8KEY_PRESSED();  // Get keypress from keypad
        if (key == '=') {  // Use '=' as an end-of-input signal
            break;  // Exit loop if '=' is pressed
        } else if (key != 0xFF) {  // If a valid key is pressed (not 0xFF which means no key pressed)
            input[cnt++] = key;
            vLCD_sendDATA('*');  // Display '*' on LCD for security
        }
        _delay_ms(300);  // Delay to avoid multiple key presses being registered
    }
    return cnt;  // Return the length of the input
}

/**
 * @brief Compares two strings.
 *
 * @param input1 Pointer to the first string.
 * @param input2 Pointer to the second string.
 * @param length Length of the strings to compare.
 * @return u8 Returns 1 if the strings match, 0 otherwise.
 *
 * This function compares two strings of the specified length and returns 1 if they are identical.
 */
u8 compare(const u8* input1, const u8* input2, u8 length) {
	while (length--) {
		if (*input1++ != *input2++) return 0;
	}
	return 1;
}

/**
 * @brief Finds the next available slot in EEPROM for a new user.
 *
 * @return u8 Returns the index of the next available slot or MAX_USERS if no slots are available.
 *
 * This function searches EEPROM for an available slot to store a new user's credentials.
 */
u8 find_next_empty_user_slot(void) {
	for (u8 user = 0; user < MAX_USERS; user++) {
		if (EEPROM_u8ReadDataByte(user * USERNAME_LENGTH + 0x0010) == 0xFF) {
			return user;
		}
	}
	return MAX_USERS;  // No available slot
}

/**
 * @brief Stores the credentials of a new user in EEPROM.
 *
 * @param user_slot Index of the slot where credentials will be stored.
 * @param username Pointer to the username string.
 * @param username_len Length of the username.
 * @param password Pointer to the password string.
 * @param password_len Length of the password.
 *
 * This function writes the username and password of a new user to the specified EEPROM slot.
 */
void store_credentials(u8 user_slot, const u8* username, u8 username_len, const u8* password, u8 password_len) {
	for (u8 i = 0; i < username_len; i++) {
		EEPROM_voidSendDataByte(user_slot * USERNAME_LENGTH + i + 0x0010, username[i]);
	}
	for (u8 i = 0; i < password_len; i++) {
		EEPROM_voidSendDataByte(user_slot * PASSWORD_LENGTH + i + 0x0040, password[i]);
	}
}

/**
 * @brief Handles the sign-up process for a new user.
 *
 * This function prompts the user to enter a username and password via Bluetooth,
 * and stores the credentials in EEPROM if a slot is available.
 */
void sign_up(void) {
	u8 username[USERNAME_LENGTH] = {0};
	u8 password[PASSWORD_LENGTH] = {0};

	vLCD_Clear();

	vLCD_Send_String("SIGNUP");
	_delay_ms(3000);

	vLCD_Clear();
	vLCD_Send_String("SIGNUP-Username:");
	vLCD_GO_TO(2,0);

	u8 username_len = get_input(username, USERNAME_LENGTH);


	vLCD_Clear();
	vLCD_Send_String("SIGNUP-Password:");
	vLCD_GO_TO(2,0);

	u8 password_len = get_input(password, PASSWORD_LENGTH);


	u8 user_slot = find_next_empty_user_slot();
	if (user_slot < MAX_USERS) {
		store_credentials(user_slot, username, username_len, password, password_len);
		vLCD_Clear();
		vLCD_Send_String("Sign Up Success");
	} else {
		vLCD_Clear();
		vLCD_Send_String("Max Users Reached");
	}
	_delay_ms(2000);
}

/**
 * @brief Checks user credentials during login.
 *
 * @param username Pointer to the entered username string.
 * @param username_len Length of the entered username.
 * @param password Pointer to the entered password string.
 * @param password_len Length of the entered password.
 * @return u8 Returns 1 if credentials match, 0 otherwise.
 *
 * This function compares the entered credentials with those stored in EEPROM.
 * If a match is found, it returns 1; otherwise, it returns 0.
 */
u8 check_credentials(const u8* username, u8 username_len, const u8* password, u8 password_len) {
	u8 stored_username[USERNAME_LENGTH] = {0};
	u8 stored_password[PASSWORD_LENGTH] = {0};

	for (u8 user = 0; user < MAX_USERS; user++) {
		for (u8 i = 0; i < USERNAME_LENGTH; i++) {
			stored_username[i] = EEPROM_u8ReadDataByte(user * USERNAME_LENGTH + i + 0x0010);
		}
		for (u8 i = 0; i < PASSWORD_LENGTH; i++) {
			stored_password[i] = EEPROM_u8ReadDataByte(user * PASSWORD_LENGTH + i + 0x0040);
		}

		if (compare(username, stored_username, username_len) &&
				compare(password, stored_password, password_len)) {
			return 1;  // Credentials match
		}
	}
	return 0;  // Credentials do not match
}

/**
 * @brief Triggers an alarm after 3 failed login attempts.
 *
 * This function activates the buzzer to alert the user after multiple failed login attempts.
 */



/**
 * @brief Closes the door using a servo motor.
 *
 * This function moves the servo motor to the closed position and displays a message on the LCD.
 */


/**
 * @brief Handles the user login process.
 *
 * This function prompts the user to enter their username and password via Bluetooth.
 * If the credentials match, the door is opened; otherwise, the number of failed attempts is updated.
 * If the number of failed attempts reaches 3, an alarm is triggered.
 */
void log_in(void) {
	static u8 number_of_trials = 0;
	u8 username[USERNAME_LENGTH] = {0};
	u8 password[PASSWORD_LENGTH] = {0};

	vLCD_Clear();

	vLCD_Send_String("LOGIN");
	_delay_ms(3000);
	vLCD_Clear();
	vLCD_Send_String("Enter Username:");
	vLCD_GO_TO(2,0);

	u8 username_len = get_input(username, USERNAME_LENGTH);

	vLCD_Clear();
	vLCD_Send_String("Enter Password:");
	vLCD_GO_TO(2,0);

	u8 password_len = get_input(password, PASSWORD_LENGTH);

	vLCD_Clear();
	vLCD_Send_String("Checking...");

	if (check_credentials(username, username_len, password, password_len)) {
		vLCD_Clear();
		vLCD_Send_String("Welcome Home!");
		_delay_ms(1000);
		EEPROM_voidSendDataByte(NUM_OF_TRIALS_ADDR, 0x00);  // Reset trials count

	} else {
		vLCD_Clear();
		vLCD_Send_String("Wrong Credentials");
		number_of_trials = EEPROM_u8ReadDataByte(NUM_OF_TRIALS_ADDR);
		EEPROM_voidSendDataByte(NUM_OF_TRIALS_ADDR, ++number_of_trials);


		_delay_ms(1000);
	}
}
