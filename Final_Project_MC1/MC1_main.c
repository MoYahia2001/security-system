 /******************************************************************************
 *
 * Module: MC1 (HMI)
 *
 * File Name: FinalProject_MC1_main.c
 *
 * Description: Source file for the MC1 (HMI) main
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#include"common_macros.h"
#include"std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"keypad.h"
#include"lcd.h"
#include"Timer0.h"
#include "uart.h"
#include "MC1.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
int password[PASSWORD_SIZE];			 // Array to store password
int confirmationPassword[PASSWORD_SIZE]; // Array to store re-enterd password
uint8 ifmatch = TRUEPASS;
uint8 press;             // stores pressed key value from keypad
uint8 receivedResponse;  // recevied flag from MC2

/*stores current state
 *  Display main options
 *  + open door
 *  - change password
 */
uint8 currentState = 0;
uint8 counter1 = 0;        // counts how many times user entered wrong password
uint8 counter2 = 0;       // counts how many times user entered wrong password

/*******************************************************************************
 *                               Main Function                                 *
 *******************************************************************************/

void main(void)
{
	/*
	 * Configuration Structure for the UART:
	 * Baud rate = 9600 kbps
	 * Eight bits data mode
	 * One stop bit
	 * No parity bits
	 */
	UART_ConfigType UART = { eight_bits, disable, one_bit, 9600 };
	UART_init(&UART);

	LCD_init();  //LCD initialization

	/*
	 * Display "Enter new password"
	 * Display "re-enter password"
	 * Check the password match
	 */
	GetNewPass_ReEnterPass_Check();


	UART_sendByte(STORE_PASS); //Send flag to MC2 to store password
	SendPass();  //Function to send password to MC2

	while (1)
	{
		switch (currentState)
		{
		 case 0:
			DisplayMainOptions(); /* display on LCD (+) open door or (-) change pass */
			press = KEYPAD_getPressedKey(); // Get pressed key from keypad
			if (press == '+')
			{
				currentState = 1;
			}
			else if (press == '-')
			{
				currentState = 2;
			}
			break;

		case 1:
			EnterPass();               // Function to enter password
			UART_sendByte(CHECK_PASS); // Send flag to MC2 to check password
			SendPass();                // Send password by UART to MC2 to check
			//receive from MC2 if password is correct or not
			receivedResponse = UART_recieveByte();
			if (receivedResponse == CORRECT_PASSWORD)
			{
				// Function that triggers motor in MC2
				OpenDoor();
			}
			else
			{
				counter1++;
				if (counter1 == 3)
				{

					LCD_clearScreen();
					LCD_displayString("Thief!          ");
					UART_sendByte(ALARM);      // Send flag to MC2 to trigger alarm
					// wait for flag form MC2 that alarm ended
					if (UART_recieveByte() == FINISHED_ALARM)
					{
						//return to display menu
						currentState = 0;
						counter1 = 0;
					}
				}
			}
			break;

		case 2:
			EnterOldPass();    			     // Function to enter old password
			UART_sendByte(CHECK_OLD_PASS);   // Send flag to MC2 to check old password from EEPROM
			SendPass();                      // Send password by UART to MC2 to check
			//receive from MC2 if password is correct or not
			receivedResponse = UART_recieveByte();
			if (receivedResponse == CORRECT_PASSWORD)
			{

				/*
				 * Display "Enter new password"
				 * Display "re-enter password"
				 * Check the password match
				 */
				GetNewPass_ReEnterPass_Check();
				//Send flag to MC2 to store password
				UART_sendByte(STORE_PASS);
				//Function to send password
				SendPass();
				currentState = 0;
			}
			else
			{
				counter2++;
				if (counter2 == 3)
				{
					LCD_clearScreen();
					LCD_displayString("Thief!          ");
					UART_sendByte(ALARM);   // Send flag to MC2 to trigger alarm

					// wait for flag form MC2 that alarm ended
					if (UART_recieveByte() == FINISHED_ALARM)
					{
						//return to display menu
						currentState = 0;
						counter2 = 0;
					}
				}

			}
			break;

		}

	}

}


/*******************************************************************************
 *                                 Functions Definitions                       *
 *******************************************************************************/


/*
 * Display "Enter new password"
 * Display "re-enter password"
 * Check the password match
 */
void GetNewPass_ReEnterPass_Check()
{

	do
	{

		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Enter New Pass:");
		LCD_moveCursor(1, 0);

		for (int i = 0; i < PASSWORD_SIZE; i++)
		{
			password[i] = KEYPAD_getPressedKey();   //Store each entered number from keypad in array
			LCD_displayCharacter('*');
			_delay_ms(4000);
		}

		while (KEYPAD_getPressedKey() != '=');
		_delay_ms(4000);

		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("Re-Enter Pass:");
		LCD_moveCursor(1, 0);

		for (int i = 0; i < PASSWORD_SIZE; i++)
		{
			confirmationPassword[i] = KEYPAD_getPressedKey();  //Store each entered number from keypad in array
			LCD_displayCharacter('*');
			_delay_ms(4000);
		}

		while (KEYPAD_getPressedKey() != '=')
			;
		_delay_ms(4000);

		for (int j = 0; j < PASSWORD_SIZE; j++)
		{
			if (password[j] != confirmationPassword[j]) // Check if passwords are matching
			{
				ifmatch = WRONGPASS;
				break;
			}

			else
				ifmatch = TRUEPASS;

		}

	} while (ifmatch == WRONGPASS);

}



//Function to send password to MC2
void SendPass()
{

	for (int i = 0; i < PASSWORD_SIZE; i++)
		{
		  UART_sendByte(password[i]);
		}
}

/* display on LCD (+) open door or (-) change pass */
void DisplayMainOptions()
{
	LCD_moveCursor(0, 0);
	LCD_displayString("+:open door     ");
	LCD_moveCursor(1, 0);
	LCD_displayString("-:change pass   ");

}


// Function that triggers motor in MC2
void OpenDoor()
{
	LCD_clearScreen();
	LCD_displayString("door is unlocked");

	// Send flag to MC2 to rotate motor Clockwise
	UART_sendByte(ROTATE_MOTOR_CW);

	// Send flag to MC2 to rotate motor Clockwise
	if (UART_recieveByte() == FINISHED_ROTATING_CW)
	{
		UART_sendByte(DELAY_3SEC);
	}
	if (UART_recieveByte() == FINISHED_DELAY)
	{
		LCD_clearScreen();
		LCD_displayString("door is locked  ");
		// Send flag to MC2 to rotate motor Clockwise
		UART_sendByte(ROTATE_MOTOR_ACW);
	}
	if (UART_recieveByte() == FINISHED_TOTAL_CYCLE)
	{
		currentState = 0;
	}

}

// Function to enter password
void EnterPass()
{
	LCD_clearScreen();
	LCD_moveCursor(0, 0);
	LCD_displayString("Enter Pass: ");
	LCD_moveCursor(1, 0);
	_delay_ms(4000);

	for (int i = 0; i < PASSWORD_SIZE; i++)
	{
		password[i] = KEYPAD_getPressedKey(); //Store each entered number from keypad in array
		LCD_displayCharacter('*');
		_delay_ms(4000);
	}

	while (KEYPAD_getPressedKey() != '=');
	_delay_ms(2000);

}

// Function to enter old password
void EnterOldPass()
{
	LCD_clearScreen();
	LCD_displayString("Enter old Pass: ");
	LCD_moveCursor(1, 0);
	_delay_ms(4000);

	for (int i = 0; i < PASSWORD_SIZE; i++)
	{
		password[i] = KEYPAD_getPressedKey(); //Store each entered number from keypad in array
		LCD_displayCharacter('*');
		_delay_ms(4000);
	}

	while (KEYPAD_getPressedKey() != '=');
	_delay_ms(4000);

}
