
/******************************************************************************************************/
/* Name: timer.h                                                                                      */
/* Author: Madonna Magdy                                                                              */
/* Version: V3                                                                                        */
/* Usage: This module contains the interface definitions for the mdio peripheral                     */
/******************************************************************************************************/

#ifndef MDIO_H_
#define MDIO_H_
/********************************  Includes  *******************************************************************************************/
#include"lstd.h"
#include "mdio_hardware_registers.h"

/*****************************  preprocessor constants **********************************************************************************************/
#define Number_OF_PORTS              (4)

#define NUMBER_OF_CHANNELS_PER_PORT  (8)

/*REGISTER NAME*/
#define DDR          (0)
#define PORT         (1)
#define PIN          (2)

#define NUM_DIO_REGISTER (3)
#define NUM_PORTS        (4)

//#define PIN4        (4)
//#define PIN0        (0)
/****************************************************************************************************************************************/

typedef enum{

	DIO_OUTPUT_PIN,

	DIO_INPUT_FLOAT_PIN,

	DIO_INPUT_PULLUP_PIN,

	DIO_MIN_STATE_VALUE=0,
	DIO_MAX_STATE_VALUE=2

}DioPinState_t;
/*****************************************************************************/

typedef enum{

 DIO_LOW_OUTPUT,

  DIO_HIGH_OUTPUT
}DioOutputValue_t;
/*****************************************************************************/

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*
 *   Defines an enumerated list of all channels (pins) for each port on the mcu device
 *   In atmega 16 each physical pin
 */
/*****************************************************************************/

typedef enum{

	PIN0_ID,  /*  --> bit0  */
	PIN1_ID,  /*  --> bit1  */
	PIN2_ID,  /*  --> bit2  */
	PIN3_ID,  /*  --> bit3  */
	PIN4_ID,  /*  --> bit4  */
	PIN5_ID,  /*  --> bit5  */
	PIN6_ID,  /*  --> bit6  */
	PIN7_ID,   /*  --> bit7  */

	MIN_NUM_PIN=0,
	MAX_NUM_PIN=7

} DioChannel_t;
/*****************************************************************************/

typedef enum{
	PORTA_ID,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID,

    MIN_NUM_PORT=0,
	MAX_NUM_PORT=3

}DioPort_t;
/*********************************************  Pointer to static function Prototype  *******************************************************************************************/
/* Function  : mdio_setPinStatus()
 *
 * Description : This function is responsible for setting a defined status for GPIO pin [OUTPUT - INPUT_FLOAT - INPUT_PULLUP]
 *
 *
 *PRE_CONDITION: the selected channel or pin is considered within the maximum DioChannel_t definition
 *PRE_CONDITION: the selected port is considered within the maximum DioPort_t definition
 *PRE_CONDITION: the selected state is considered within the maximum DioPinState_t definition
 *
 *POST_CONDITION:the pin status will be au8_status
 *
 * Return: void
 *
 * */
void mdio_setPinStatus(DioPort_t au8_port, DioChannel_t au8_pin, DioPinState_t au8_status);
/****************************************************************************************************************************************/


/****************************************************************************************************************************************/
/* Function  : mdio_setPinValue()
 *
 * Description : This function is responsible for setting a defined value for an OUTPUT GPIO pin [HIGH - LOW]
 *
 * PRE_CONDITION:  the selected channel must be configured as GPIO Channel
 * PRE_CONDITION: the selected channel must be configured as output
 *
 *
 *PRE_CONDITION: the selected channel or pin is considered within the maximum DioChannel_t definition
 *PRE_CONDITION: the selected port is considered within the maximum DioPort_t definition
 *PRE_CONDITION: the selected value is considered within the maximum DioOutputValue_t definition
 *
 *POST_CONDITION:the output pin value will be au8_value
 *
 * Return: void
 *
 * */
void mdio_setPinValue(DioPort_t au8_port, DioChannel_t au8_pin, DioOutputValue_t au8_value);
/****************************************************************************************************************************************/


/****************************************************************************************************************************************/
/* Function    : mdio_setPinStatus()
 *
 * Description : This function is responsible for toggling a defined value for an OUTPUT GPIO pin
 *
 *
 *PRE_CONDITION: the selected channel or pin is considered within the maximum DioChannel_t definition
 *PRE_CONDITION: the selected port is considered within the maximum DioPort_t definition
 *PRE_CONDITION: the selected state is considered within the maximum DioPinState_t definition
 *
 *POST_CONDITION:the pin status will be au8_status
 *
 * Return: void
 *
 * */
void mdio_togglePinValue(DioPort_t au8_port, DioChannel_t au8_pin);
/****************************************************************************************************************************************/


/****************************************************************************************************************************************/
/*This function is responsible for reading a defined value for an INPUT GPIO pin [HIGH - LOW]*/
void GPIO_setupPortDirection(DioPort_t au8_port, GPIO_PortDirectionType au8_direction);
/****************************************************************************************************************************************/


/****************************************************************************************************************************************/
/* Function Name : GPIO_readPort
 *
 * Description : This function is responsible for copying the value of the port register into an u8_t variable type
 * *
 *PRE_CONDITION: the selected port is considered within the maximum au8_port definition
 *
 *
 *POST_CONDITION:the pin status will be au8_status
 *
 * Return: variable with  unsigned char type
 *
 * */
u8_t GPIO_readPort(u8_t au8_port);
/****************************************************************************************************************************************/


/****************************************************************************************************************************************/
/* Pointer Name : Ptr_GPIO_writePort
 *
 * Description : This function is responsible for writting a value in the PORT register
 *PRE_CONDITION: the DDR register must be initialized to 1 --> output port
 *
 *POST_CONDITION:the selected port --> au8_port  will have a value of u8_t au8_value
 *
 * Return: variable with  unsigned char type
 *
 * */
void GPIO_writePort(u8_t au8_port, u8_t au8_value);
/****************************************************************************************************************************************/
u8_t  mdio_getPinValue(DioPort_t au8_port, DioChannel_t au8_pin);

#endif /* MDIO_H_ */
