 /******************************************************************************
 *
 * Module: MC2
 *
 * File Name: MC2_main.c
 *
 * Description: Source file for the MC2 main
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include"common_macros.h"
#include"MC2.h"
#include"std_types.h"
#include"external_eeprom.h"
#include"twi.h"
#include"dcmotor.h"
#include"Timer0.h"
#include"uart.h"
#include"buzzer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 receivedpass[5];  // Array stores received password from MC1
uint16 recieve;         // variable stores all flags received from MC1
uint8 checkPass[5];     // Array stores password read from EEPROM
uint16 g_tick=0;        // variable stores number of overflows of timer


/*******************************************************************************
 *                                 Main Function                               *
 *******************************************************************************/

void main(void)
{
	/* Enable global interrupt */
	SREG |= (1<<7);

	/*
	 * Configuration Structure for the UART:
	 * Baud rate = 9600 kbps
	 * Eight bits data mode
	 * One stop bit
	 * No parity bits
	 */
	UART_ConfigType UART ={eight_bits,disable,one_bit,9600};
	UART_init(&UART);

	/*
	 * Configuration Structure for the TWI:
	 * SCL Frequency
	 * SLAVE_ADDRESS = 0x1
	 */
	TWI_ConfigType TWI = {400000,0x01};
	TWI_init(&TWI);

	/*
	 * Configuration structure for the timer:
	 * 1.Overflow mode
	 * 2.initial value=0
	 * 3.prescaler = 1024
	 * 4.compare value = 0 (not used in case of overflow mode)
	 */
	Timer0_ConfigType Timer0 = { normal, 0 , 0 , F_CPU_1024 };

	DcMotor_Init();  // Set direction for motor pins
	Buzzer_Init();   // Set direction for buzzer pin

	while(1)
	{
		recieve = UART_recieveByte();        // receive and store all flags from MC1

		switch(recieve)                		 // switch on received flag
		{
		  case STORE_PASS:
			             recievePass(); 	// receive password from MC1
			             SavePass();    	// save password received from MC1 in EEPROM
		                 break;

		  case  CHECK_PASS:
			  	  	  	 recievePass();          // receive password from MC1
	                     if(CheckPass() == 1)    // if password mathes
	                     { UART_sendByte(CORRECT_PASSWORD); }  // send flag to MC1
	                     else
	                     { UART_sendByte(FALSE_PASSWORD); }    // send flag to MC1

	                     break;



		  case ROTATE_MOTOR_CW:

			  	  	  	  	  	  // assigning call back function of the timer
			  	  	  	  	  	  Timer0_setcallBack(g_tickCounterMotor_CW);
			  	  	  	  	  	  // send config. of timer
			  	  	  	  	  	  Timer0_init(&Timer0);
			  	  	  	  	  	  // Make motor rotate Clockwise for 15 sec
			  	  	  	  	  	  DcMotor_Rotate(CW);
			  	  	  	  	  	  break;


		  case  DELAY_3SEC:
			  	  	  	  	  	  // assigning call back function of the timer
								  Timer0_setcallBack(g_tickHoldMotor);
			  	  	  	  	  	  // send config. of timer
								  Timer0_init(&Timer0);
			  	  	  	  	  	  // Hold motor for 3 sec
								  DcMotor_Rotate(STOP);
								  break;

		 case ROTATE_MOTOR_ACW:
			 	 	 	 	 	  // assigning call back function of the timer
								  Timer0_setcallBack(g_tickCounterMotor_ACW);
			  	  	  	  	  	  // send config. of timer
								  Timer0_init(&Timer0);
			  	  	  	  	  	  // Make motor rotate Anti Clockwise for 15 sec
								  DcMotor_Rotate(A_CW);
								  break;

		 case ALARM:              // Make buzzer ring for 1 minute

			                      // Set pin of buzzer to 1
	  	  	  	                  Buzzer_On();
			 	 	 	 	 	  // assigning call back function of the timer
	  	  	  	  	  	  	  	  Timer0_setcallBack(g_tickCounter_Alarm);
			  	  	  	  	  	  // send config. of timer
			  	  	  	  	  	  Timer0_init(&Timer0);
			 	 	 	 	 	  break;

		  case CHECK_OLD_PASS:
			  	  	  	  	  	  	recievePass();            // receive password from MC1
									if (CheckOldPass() == 1)  // if password matches
									{
										UART_sendByte(CORRECT_PASSWORD);  // send flag to MC1
									}
									else
									{
										UART_sendByte(FALSE_PASSWORD);    // send flag to MC1
									}
									break;

		}

	}

}


/*******************************************************************************
 *                                 Functions Definitions                       *
 *******************************************************************************/


//Function to receive password from MC1
void recievePass()
{
	for(int i=0; i<5; i++ )
	{
	   receivedpass[i] = UART_recieveByte();   // receive password in Array
	}

}

// save password received from MC1 in EEPROM
void SavePass()
{

	for (int i = 0; i < 5; i++)
	{
		EEPROM_writeByte(0x0311 + i, receivedpass[i]);  // save received password in EEPROM
		_delay_ms(100);
	}

}

// checks if received Password from MC1 matches the Password saved in EEPROM
uint8 CheckPass()
{
	for (int i = 0; i < 5; i++)
	{
			EEPROM_readByte(0x0311 + i, &checkPass[i]);   // read saved password in EEPROM
			_delay_ms(100);
	}

	for (int i = 0; i < 5; i++)
	{
		if(receivedpass[i] !=  checkPass[i])             // Check if passwords are matching
			return 0;
	}

	return 1;

}


// checks if received Password from MC1 matches the Old Password saved in EEPROM
uint8 CheckOldPass()
{
	for (int i = 0; i < 5; i++)
	{
		EEPROM_readByte(0x0311 + i, &checkPass[i]);   // read saved password in EEPROM
		_delay_ms(100);
	}


	for (int i = 0; i < 5; i++)
	{
		if (receivedpass[i] != checkPass[i])           // Check if passwords are matching
			return 0;
	}

	return 1;
}


/*
 *  Description : Function to handle a time-dependant operation
 * 	Counts 15 seconds to open the door
 */
void g_tickCounterMotor_CW()
{
	g_tick++;

	if(g_tick==458)
	{
		Timer0_deinit();                      // Turn off timer
		g_tick=0;                             // start g_ticks from 0 again
		UART_sendByte(FINISHED_ROTATING_CW);  // send flag to MC1 that motor finished rotating Clockwise

	}

}

/*
 * Description : Function to handle the time-dependant operation
 * Counts 3 seconds in which the motor is stopped
 */

void g_tickHoldMotor()
{
	g_tick++;

		if(g_tick==92)
		{
			Timer0_deinit();                 // Turn off timer
			g_tick=0;                        // start g_ticks from 0 again
			UART_sendByte(FINISHED_DELAY);   // send flag to MC1 that motor finished his holding delay
		}

}


/*
 * Description : Function to handle the time-dependant operation
 * Counts 15 seconds while closing the door then stops the motor
 */
void g_tickCounterMotor_ACW()
{
	g_tick++;

	if(g_tick==458)
	{
		Timer0_deinit();                       // Turn off timer
		g_tick=0;                              // start g_ticks from 0 again
    	DcMotor_Rotate(STOP);                  // Turn off motor
		UART_sendByte(FINISHED_TOTAL_CYCLE);   // send flag to MC1 that motor finished rotating totally
	}

}

/*
 * Description : Function to handle the time-dependant operation
 * Counts 60 seconds in case of 3 wrong password entries and then turns off buzzer
 */
void g_tickCounter_Alarm()
{
	g_tick++;

	if(g_tick==1831)
	{
		Timer0_deinit();                  // Turn off timer
		g_tick=0;                         // start g_ticks from 0 again
		Buzzer_Off();                     // Turn off buzzer
		UART_sendByte( FINISHED_ALARM );  // send flag to MC1 that alarm finished
	}

}
