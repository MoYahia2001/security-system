/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Buzzer Port Configurations */
#define BUZZER_PORT_ID    PORTC_ID
#define BUZZER_PIN_ID     PIN2_ID

/* Keypad button logic configurations */
#define BUZZER_ON          LOGIC_HIGH
#define BUZZER_OFF         LOGIC_LOW


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Buzzer:
 * 1. Setup the Buzzer pin direction by using the GPIO driver.
 */
void Buzzer_Init();

/*
 * Description :
 * Turns on the buzzer
 */
void Buzzer_On();

/*
 * Description :
 * Turns off the buzzer
 */
void Buzzer_Off();


#endif /* BUZZER_H_ */
