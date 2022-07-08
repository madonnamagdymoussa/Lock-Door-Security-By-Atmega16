/******************************************************************************************************/
/* Name: keypad.h                                                                                      */
/* Author: Madonna Magdy                                                                              */
/* Version: V1                                                                                        */
/* Usage: This module contains the interface definitions for the keypad peripheral                     */
/******************************************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include"lstd.h"
//#include"mdio.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                  4
#define KEYPAD_NUM_ROWS                  4

/* Keypad Port Configurations */
#define KEYPAD_PORT_ID                   PORTA_ID

#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID        PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            DIO_HIGH_OUTPUT
#define KEYPAD_BUTTON_RELEASED           DIO_LOW_OUTPUT

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button
 */
u8_t KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */
