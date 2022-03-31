/******************************************************************************
 *
 * Module: DC-Motor
 *
 * File Name: dcmotor.c
 *
 * Description: source file for the DC-Motor driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "gpio.h"
#include "dcmotor.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void DcMotor_Init(void)
{
	/*Set IN1 & IN2 as output pins */
	GPIO_setupPinDirection(INPUT_1_PORT , INPUT_1_PIN , PIN_OUTPUT);
	GPIO_setupPinDirection(INPUT_2_PORT , INPUT_2_PIN , PIN_OUTPUT);

	/* Stop motor at beginning */
	GPIO_writePin(INPUT_1_PORT, INPUT_1_PIN, LOGIC_LOW);
	GPIO_writePin(INPUT_2_PORT, INPUT_2_PIN, LOGIC_LOW);
}


void DcMotor_Rotate(DcMotor_State state)
{
	/* Rotate Motor ClockWise */
	if (state == CW)
	{
		GPIO_writePin(INPUT_2_PORT, INPUT_2_PIN, LOGIC_LOW);
		GPIO_writePin(INPUT_1_PORT, INPUT_1_PIN, LOGIC_HIGH);
	}

	/* Rotate Motor Anti-ClockWise */
	else if (state == A_CW)
	{
		GPIO_writePin(INPUT_2_PORT, INPUT_2_PIN, LOGIC_HIGH);
		GPIO_writePin(INPUT_1_PORT, INPUT_1_PIN, LOGIC_LOW);
	}

	/* Stop motor */
	else if (state == STOP)
	{
		GPIO_writePin(INPUT_1_PORT, INPUT_1_PIN, LOGIC_LOW);
		GPIO_writePin(INPUT_2_PORT, INPUT_2_PIN, LOGIC_LOW);
	}


}
