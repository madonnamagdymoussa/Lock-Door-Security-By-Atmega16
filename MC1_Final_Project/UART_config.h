/****************************************************************************************************/
/* Name: UART_config.h                                                                             */
/* Author: Madonna Magdy                                                                             */
/* Version: V2                                                                                       */
/* Usage: This module contains the interfacing definition of  the UART peripheral configurations    */
/****************************************************************************************************/

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define TRANSMITTER_ENABLE  (3)
#define RECEIVER_ENABLE     (4)
/***************************************************************************************/
/*UART Baud rates*/
typedef enum{
 MUART_2400_BR   = 416,
 MUART_4800_BR   = 207,
 MUART_9600_BR   = 103,
 MUART_19200_BR  = 51,
 MUART_115200_BR =  8
}MUART_BaudRate_t;
/***************************************************************************************/
/* set the value according to control register C   */
typedef enum{
	ASYNCH =0, /* clearing bit 6 */
	SYNCH =1  /* setting  bit 6 */

}MUART_SyncMode_t;

#define  USART_MODE_SELECT_BIT  (6)
/***************************************************************************************/
/* set the value according to control register C */
/* Parity mode bits number 4 and 5*/
typedef enum{
	NO_PARITY =0,   /*clearing  bit number 4 and  5 */
	EVEN_PARITY =1,  /* setting bit number 4 and clearing bit number5 */
	ODD_PARITY =3   /*setting bit number 4 and  5 */
}MUART_ParityMode_t;

#define PARITY_BIT  (4)
/***************************************************************************************/
/* set the value according to control register C   */
/* the Stop Bit Select is bit number 3  */
typedef enum{
	ONE_STOP_BIT =0,     /* clearing the stop select bit  */
	TWO_STOP_BIT =1    /* setting the stop select bit  */
}MUART_StopBit_t;

#define STOP_SELECT_BIT    (3)
/***************************************************************************************/
/* set the value according to control register C */
/* the Character Size bits number 1 and 2  */
typedef enum{
	_5_DATA_BIT =0,    /* clearing bits 1 and 2 */
	_6_DATA_BIT =1,    /* setting bit 1 and clearing bit 2 */
	_7_DATA_BIT =2,     /* clearing bit 1 and setting bit 2 */
	_8_DATA_BIT =3,   /* setting bits 1 and 2 */

}MUART_DataBit_t;

#define  CHARACTER_SIZE_BIT (1)
/***************************************************************************************/

typedef struct {
	MUART_BaudRate_t baudRate;
	MUART_SyncMode_t syncMode;
	MUART_ParityMode_t parityMode;
	MUART_StopBit_t  stopBit;
	MUART_DataBit_t  dataBit;


}MUART_Config_t;

MUART_Config_t MCU1;

//MUART_Config_t MCU2;

#endif /* UART_CONFIG_H_ */
