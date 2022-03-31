 /******************************************************************************
 *
 * Module: DC-Motor
 *
 * File Name: dcmotor.h
 *
 * Description: header file for the DC-Motor driver
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define INPUT_1_PORT        PORTD_ID
#define INPUT_1_PIN         PIN2_ID

#define INPUT_2_PORT        PORTD_ID
#define INPUT_2_PIN         PIN3_ID


typedef enum
{
	 STOP  , CW , A_CW
}DcMotor_State;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver
 * Stop at the DC-Motor at the beginning through the GPIO driver
 * */
void DcMotor_Init(void);

/*
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state valu
 * Send the required duty cycle to the PWM driver based on the required speed value
 */
void DcMotor_Rotate(DcMotor_State state);


#endif /* DCMOTOR_H_ */
