 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


typedef enum
{
   five_bits = 0 , six_bits = 1 , seven_bits = 2 , eight_bits = 3 , nine_bits = 7

}UART_NumberofBitsperFrame;


typedef enum
{
   disable = 0 , even_parity = 2 , odd_parity = 3

}UART_Paritytype;


typedef enum
{
	one_bit = 0 , two_bits = 1

}UART_NumberofstopBits;



typedef struct
{
	UART_NumberofBitsperFrame  No_bits_frame;
	UART_Paritytype            parity;
	UART_NumberofstopBits      No_stop_bits;
	uint32                     baud_rate;
}UART_ConfigType;



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init( UART_ConfigType* Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
