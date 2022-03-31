/******************************************************************************
 *
 * Module: MC2
 *
 * File Name: MC2_main.c
 *
 * Description: Header file for the MC2 main
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#ifndef MC2_H_
#define MC2_H_

#include "std_types.h"

/*******************************************************************************
 *                                 Definitions                                      *
 *******************************************************************************/

#define PASSWORD_SIZE     5
#define TRUEPASS          1
#define WRONGPASS         0

#define PASSWORD_SIZE     5
#define TRUEPASS          1
#define WRONGPASS         0

#define STORE_PASS        'a'
#define CHECK_PASS        'b'
#define ROTATE_MOTOR_CW   'c'
#define ROTATE_MOTOR_ACW  'd'
#define ALARM             'e'
#define CHECK_OLD_PASS    'g'
#define DELAY_3SEC        's'

#define CORRECT_PASSWORD     'y'
#define FALSE_PASSWORD       'p'
#define FINISHED_ROTATING_CW 'x'
#define FINISHED_TOTAL_CYCLE 'f'
#define FINISHED_ALARM       'm'
#define FINISHED_DELAY       't'


/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/
void recievePass();
void SavePass();
uint8 CheckPass();
uint8 CheckOldPass();
void g_tickCounterMotor_CW();
void g_tickCounterMotor_ACW();
void g_tickCounter_Alarm();
void g_tickHoldMotor();

#endif /* MC2_H_ */
