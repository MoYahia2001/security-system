/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: Timer0.c
 *
 * Description: Source file for the Timer0 AVR driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#include "Timer0.h"
#include "gpio.h"
#include "avr/io.h"
#include <avr/interrupt.h> /* For Timer0 ISR */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* Interrupt Service Routine for timer0 overflow mode */

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

/* Interrupt Service Routine for timer0 compare mode */

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}

}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description : Function to initialize the Timer0 driver
 * 	1. Set the mode.
 * 	2. Set the initial value.
 * 	3. Set the compare value.
 * 	4. Set the prescaler.
 */

void Timer0_init(Timer0_ConfigType* Config_Ptr)
{
	if(Config_Ptr->mode == normal)
	{
	    TCNT0 = Config_Ptr->initial_value;           // Set Timer initial value
	    TIMSK |= (1<<TOIE0);                         // Enable Timer0 Overflow Interrupt
		/* Configure the timer control register */
		TCCR0 |= (1<<FOC0) ;
		TCCR0 &=  ~(1<<WGM01) &~ (1<<WGM00) ;
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler) ;
	}

	else if(Config_Ptr->mode == CTC)
	{
		TCNT0 = Config_Ptr->initial_value;           // Set Timer initial value
		OCR0 = Config_Ptr->compare_value;           // Set Compare Value
		TIMSK |= (1 << OCIE0);                // Enable Timer0 Compare Interrupt
		/* Configure the timer control register */
		TCCR0 |= (1 << FOC0);
		TCCR0 &= ~(1 << WGM00);
		TCCR0 |=  (1 << WGM01);
		TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->prescaler);
	}

}

/*
 * Description: Function to set the Call Back function address.
 */

void Timer0_setcallBack(void(*b_ptr)(void))
{

	/* Save the address of the Call back function in a global variable */
		g_callBackPtr = b_ptr;

}

/*
 * Description: Function to disable the Timer0 to stop the Timer Driver
 */

void Timer0_deinit(void)
{
	/* No clock source */
	TCCR0 &= ~(1 <<CS02) &~(1 <<CS01) &~(1 <<CS00);

}
