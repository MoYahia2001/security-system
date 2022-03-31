/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"
#include "avr/io.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Buzzer:
 * 1. Setup the Buzzer pin direction by using the GPIO driver.
 */
void Buzzer_Init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}

/*
 * Description :
 * Turns on the buzzer
 */
void Buzzer_On()
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*
 * Description :
 * Turns off the buzzer
 */
void Buzzer_Off()
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
