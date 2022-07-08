/*********************************************************************************************/
/* Name: UART_config.c                                                                      */
/* Author: Madonna Magdy                                                                     */
/* Version: V2                                                                               */
/* Usage: This module contains the implementation for the uart peripheral configurations    */
/*********************************************************************************************/

#include"UART_config.h"

MUART_Config_t MCU1 ={

		MUART_9600_BR,
		ASYNCH,
		NO_PARITY,
		ONE_STOP_BIT,
		_8_DATA_BIT

};
