#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include <math.h>
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/DIO/DIO_Config.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include "MCAL/UART/UART_Int.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/ADC/ADC_Config.h"
#include "MCAL/TWI/TWI_Interface.h"

#include "HAL/SERVO/SERVO.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"
#include "HAL/KEYPAD/KPD_Interface.h"

#include "app/service.h"




#define PASSWORD_LENGTH 5
#define USERNAME_LENGTH 5
#define MAX_USERS 10
#define NUM_OF_TRIALS_ADDR 25
#define UPDATE_THRESHOLD 1
#define LDR_UPDATE_THRESHOLD 1


// Global variables
u8 trails = 3; // Number of login atTempts remaining

/*
// Array of predefined users for authentication
static User users[MAX_USERS] = {
		{"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"}, {"user4", "pass4"}, {"user5", "pass5"},
		{"user6", "pass6"}, {"user7", "pass7"}, {"user8", "pass8"}, {"user9", "pass9"}, {"user10", "pass10"}
};
 */


int main() {

	TWI_voidMasterInit(0);
	app_init();
	// Display initial messages on the LCD
	welcome_message(); // Send "HELLO" to LCD
	_delay_ms(2000); // Delay for 900 milliseconds




	u8 choice;
	u16 readdigit=0;
	u16 readdigit2=0;
	u32 Temp=0,VOIL = 0;
	u32 prevReading = 0xFFFFFFFF;
	u32 LDRprevReading = 0xFFFFFFFF;

	u32 LDR_room=0;
	u8 start =1;
	u8 start2 =1;





	// Outer menu to choose between login and signup
	while (1) {
		if (start) {
			vLCD_Clear(); // Clear the LCD screen
			vLCD_Send_String("1-Login 2-SignUp"); // Display options for login and signup
			start=0;
		}
		else{
			choice = u8KEY_PRESSED();
			if(choice != 0xff) {
				if (choice-'0' == 1) {
					//vLCD_Clear(); // Clear the LCD screen
					//vLCD_Send_String("ok"); // Display options for login and signup
					//_delay_ms(900); // Delay for 900 milliseconds
					// Proceed to login
					break; // Exit the loop and continue with login
				} else if (choice-'0' == 2) {
					// Proceed to sign up
					sign_up();  // Call sign-up function
					_delay_ms(900); // Delay for 900 milliseconds
					start=1;
					//break;
				} else {
					vLCD_Clear(); // Clear the LCD screen
					vLCD_Send_String("Invalid Choice"); // Display an error message
					_delay_ms(900); // Delay for 900 milliseconds
					start=1;
				}
			}}}

	while (trails > 0) { // Loop until the user has no remaining atTempts
		vLCD_Clear(); // Clear the LCD screen

		log_in();  // Handle login using EEPROM

		// Check if login was successful
		if (EEPROM_u8ReadDataByte(NUM_OF_TRIALS_ADDR) == 0) {
			vLCD_Clear();
			vLCD_Send_String("Login Success");
			_delay_ms(900);
			// Continue with control mode...
			// Turn off specific output pins to indicate success
			vSet_Pin_OUTPUTvalue(PORT_A, PIN_3, LOW); // Turn off device connected to pin 3
			//vSet_Pin_OUTPUTvalue(PORT_A, PIN_5, LOW); // Turn off device connected to pin 5
			break;  // Exit the loop after successful login
		}

		else
		{
			trails--; // Decrement the remaining login atTempts
			vLCD_Clear(); // Clear the LCD screen
			if (trails == 0)
			{
				vLCD_Send_String("Locked Out"); // Display locked out message
				vSet_Pin_OUTPUTvalue(PORT_A, PIN_4, HIGH); /* buzzer */ // Activate buzzer
				//vSet_Pin_OUTPUTvalue(PORT_A, PIN_5, HIGH); // Activate another device
				_delay_ms(900); // Delay for 900 milliseconds
			}
			else
			{
				vLCD_Send_String("Invalid Login"); // Display invalid login message
				_delay_ms(900); // Delay for 900 milliseconds
			}
		}
	}







	// If there are remaining login atTempts, enter control mode
	if (trails > 0)
	{
		while (1)
		{ // Infinite loop for control operations
			if (start2) {
				vLCD_Clear();
				vLCD_Send_String("  ###Control###"); // Display control menu
				_delay_ms(2000);
				vLCD_Clear(); // Clear the LCD screen
				vLCD_Send_String("1-LED 2-DOOR"); // Display options for LED and door control
				vLCD_GO_TO(2,0);
				vLCD_Send_String("3-TempDeg 4-Light"); // Display options for LM35 and LDR
				_delay_ms(900); // Delay for 900 milliseconds
				start2=0;
			}
			else{
				u8 received_operation = u8KEY_PRESSED(); // Receive operation choice from UART
				if(received_operation != 0xff) {
					if (received_operation-'0' == 1)
					{ // If LED control is selected
						vLCD_Clear(); // Clear the LCD screen
						vLCD_Send_String("1-LED ON"); // Display LED ON option
						vLCD_GO_TO(2,0); // Move cursor to second line, first column
						vLCD_Send_String("2-LED OFF"); // Display LED OFF option
						while(1){
							u8 received_led_status = u8KEY_PRESSED(); // Receive LED control choice from UART
							if(received_led_status != 0xff) {
								if (received_led_status-'0' == 1)
								{
									vSet_Pin_OUTPUTvalue(PORT_A, PIN_3, HIGH); // Turn on LED connected to pin 3
									//UART_TransmitString("on"); // Send "on" status to UART
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("LED ON"); // Display LED ON message
									_delay_ms(3000); // Delay for 900 milliseconds
									start2=1;
									received_led_status=0;
									break;
								}
								else if (received_led_status-'0' == 2)
								{
									vSet_Pin_OUTPUTvalue(PORT_A, PIN_3, LOW); // Turn off LED connected to pin 3
									//UART_TransmitString("off"); // Send "off" status to UART
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("LED OFF"); // Display LED OFF message
									_delay_ms(3000); // Delay for 900 milliseconds
									start2=1;
									received_led_status=0;
									break;
								}

								else
								{
									//UART_TransmitString("none"); // Send "none" status to UART
									vLCD_Clear(); // Clear the LCD screen
									//vLCD_Send_String("NONE"); // Display NONE message
									vLCD_sendDATA(received_led_status); // Display NONE message

									_delay_ms(900); // Delay for 900 milliseconds
									start2=0;
									received_led_status=0;
									break;
								}

							}


							_delay_ms(500); // Adjust delay as needed


						}
					}
					else if ( (received_operation-'0') == 2)
					{ // If door control is selected
						vLCD_Clear(); // Clear the LCD screen
						vLCD_Send_String("1-LOCK DOOR"); // Display lock door option
						vLCD_GO_TO(2,0); // Move cursor to second line, first column
						vLCD_Send_String("2-UNLOCK DOOR"); // Display unlock door option


						while(1){
							u8 received_lock_status = u8KEY_PRESSED(); // Receive door control choice from UART

							if(received_lock_status != 0xff) {


								if (received_lock_status-'0' == 1)
								{
									vTIMER1_START();

									servo_angle(0); // Lock the door by setting servo angle to 0
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("DOOR LOCKED"); // Display door locked message
									_delay_ms(3000); // Delay for 900 milliseconds
									start2=1;
									received_lock_status=0;
									break;
									vTIMER1_STOP();

								}
								else if (received_lock_status-'0' == 2)
								{
									vTIMER1_START();

									servo_angle(180); // Unlock the door by setting servo angle to 90
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("DOOR UNLOCKED"); // Display door unlocked message
									_delay_ms(3000); // Delay for 900 milliseconds
									start2=1;
									received_lock_status=0;
									break;
									vTIMER1_STOP();

								}

							}


							_delay_ms(500); // Adjust delay as needed

						}
					}
					else if (received_operation-'0' == 3)
					{
						//////////////////////////////////////////////////

						while (1) {


							u32 totalReading = 0;
							for (int i = 0; i < 10; i++) {
							    totalReading += MADC_u8StartConversion(CHANNEL_7);
							}
							readdigit = totalReading / 10;

							//readdigit = MADC_u8StartConversion(CHANNEL_7);

							if (readdigit != 0) { // Ensure a valid reading is obtained
								VOIL = (u32)(readdigit * 2560UL) / 1024; // Convert ADC value to voltage
								Temp = VOIL / 10; // Convert voltage to Temperature

								// Update LCD only if temperature has changed beyond threshold
								if (abs((int)(Temp - prevReading)) >= UPDATE_THRESHOLD) {
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("Temp:");
									vLCD_GO_TO(1, 6);
									vLCD_Convert_numTOchar(Temp);
									vLCD_Send_String(" C");

									// Control fan speed based on temperature
									if ((Temp >= 20) && (Temp <= 35)) {
										vTimer2_SetOCRValue(127);
										vLCD_GO_TO(2, 0);
										vLCD_Send_String("Fan:half speed");
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, LOW);
									} else if ((Temp > 25) && (Temp <= 30)) {
										vTimer2_SetOCRValue(191);
										vLCD_GO_TO(2, 0);
										vLCD_Send_String("Fan:75% speed");
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, LOW);
									} else if ((Temp > 30) && (Temp <= 45)) {
										vTimer2_SetOCRValue(255);
										vLCD_GO_TO(2, 0);
										vLCD_Send_String("Fan:full speed");
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, LOW);
									} else if (Temp > 45) {
										vTimer2_SetOCRValue(0);
										vLCD_GO_TO(2, 0);
										vLCD_Send_String("Fire warning!!");
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, HIGH); // Red LED ON
									} else {
										vTimer2_SetOCRValue(0);
										vLCD_GO_TO(2, 0);
										vLCD_Send_String("Fan OFF");
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, LOW);
									}

									vTIMER2_Start();

									prevReading = Temp; // Update previous temperature

								}
							} else {
								vLCD_Clear();
								vLCD_Send_String("Error"); // Display error message if ADC read fails

							}

							// Check for '0' key press to return to control menu
							u8 Back1 = u8KEY_PRESSED();
							if(Back1!=0xff){
								if(Back1 - '0' == 0) {
									start2=1;
									vSet_Pin_OUTPUTvalue(PORT_C, PIN_5, LOW);
									break;
								}
							}
							_delay_ms(500); // Adjust delay as needed
						}


					}
					else if(received_operation-'0' == 4)
					{
						while(1){
							readdigit2 = MADC_u8StartConversion(CHANNEL_0);

							if (readdigit2 != 0) { // Ensure a valid reading is obtained

								//#########################  Room 1 #############################
								//For the LDR, MAX Vo = (5*5.5k)/(5.5k+5k)=2.62 V (DARK)
								//For the LDR, MIN Vo = (5*1.5k)/(1.5k+5k)=0.8 V (LIGHT)
								LDR_room = (u32)(readdigit2 * 2560UL) / 1024UL; // Convert ADC value to voltage

								// Update LCD only if temperature has changed beyond threshold
								if (abs((int)(LDR_room - LDRprevReading)) >= LDR_UPDATE_THRESHOLD) {
									vLCD_Clear(); // Clear the LCD screen
									vLCD_Send_String("Light:");
									vLCD_GO_TO(1, 7);
									vLCD_Convert_numTOchar(LDR_room);
									vLCD_Send_String(" mv");

									if (LDR_room < 1000)
									{
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_2, HIGH);
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_3, HIGH);
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_4, HIGH);
									}
									else
									{
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_2, LOW);
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_3, LOW);
										vSet_Pin_OUTPUTvalue(PORT_C, PIN_4, LOW);
									}

									LDRprevReading = LDR_room; // Update previous temperature

								}


							} else {
								//vLCD_Clear();
								//vLCD_Send_String("Error"); // Display error message if ADC read fails

							}

							// Check for '0' key press to return to control menu
							u8 Back2 = u8KEY_PRESSED();
							if(Back2!=0xff){
								if(Back2 - '0' == 0) {
									start2=1;
									break;
								}
							}

							_delay_ms(500); // Adjust delay as needed
						}
					}
				}
			}
		}
	}





	return 0; // Return 0 to indicate successful execution
}


