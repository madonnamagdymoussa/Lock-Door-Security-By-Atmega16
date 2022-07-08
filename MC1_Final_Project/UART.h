
/******************************************************************************************************/
/* Name: UART.h                                                                                      */
/* Author: Madonna Magdy                                                                              */
/* Version: V2                                                                                       */
/* Usage: This module contains the interface definitions for the uart peripheral                     */
/******************************************************************************************************/


#ifndef UART_H_
#define UART_H_

#include"lstd.h"
#include"UART_config.h"

void UART_init(MUART_Config_t *ptr_uart_config);

u8_t UART_ByteRecieved(void);

u8_t UART_IS_ByteRecieved(u8_t *ptr_data);

void UART_SendByte(u8_t data);

void UART_SendString(u8_t* str);

void UART_ReceiveString(u8_t* str);

#endif /* UART_H_ */
