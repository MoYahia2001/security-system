/******************************************************************************
 *
 * Module: MC1 (HMI)
 *
 * File Name: FinalProject_MC1_main.c
 *
 * Description: Header file for the MC1 (HMI) main
 *
 * Author: Mohamed Yahia
 *
 *******************************************************************************/

#ifndef MC1_H_
#define MC1_H_

/*******************************************************************************
 *                                 Definitions                                      *
 *******************************************************************************/

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

#define CORRECT_PASSWORD  'y'
#define FALSE_PASSWORD    'p'
#define FINISHED_ROTATING_CW 'x'
#define FINISHED_TOTAL_CYCLE 'f'
#define FINISHED_ALARM       'm'
#define FINISHED_DELAY       't'

/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/

void GetNewPass_ReEnterPass_Check();
void SendPass();
void DisplayMainOptions();
void OpenDoor();
void EnterPass();
void EnterOldPass();

#endif /* MC1_H_ */
