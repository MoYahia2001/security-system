/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.h
 *
 * Description: Header file for the Timer0 AVR driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum
{
	normal , PWM_PhaseCorrect , CTC , Fast_PWM

}Timer0_Mode;


typedef enum
{
	no_clock, F_CPU_1, F_CPU_8, F_CPU_64 ,F_CPU_256 ,F_CPU_1024 ,External_Falling ,External_rising

}Timer0_Prescaler;


typedef struct
{
	Timer0_Mode      mode;
    uint8            initial_value;
	uint8            compare_value;
	Timer0_Prescaler prescaler;

}Timer0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the Timer0 driver
 * 	1. Set the mode.
 * 	2. Set the initial value.
 * 	3. Set the compare value.
 * 	4. Set the prescaler.
 */

void Timer0_init(Timer0_ConfigType* Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */

void Timer0_setcallBack(void(*b_ptr)(void));

/*
 * Description: Function to disable the Timer0 to stop the Timer Driver
 */

void Timer0_deinit(void);

#endif /* TIMER0_H_ */
