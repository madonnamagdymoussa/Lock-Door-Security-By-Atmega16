/******************************************************************************************************/
/* Name   : UART.c                                                                                     */
/* Author : Madonna Magdy                                                                             */
/* Version: V2                                                                                        */
/* Usage  : This module contains the implementation for the UART driver functions                      */
/******************************************************************************************************/


/***************************************************  Includes *************************************************************/
#include "lstd.h"
#include "lbit.h"
#include "UART_hardware_registers.h"
//#include "UART_config.h"
#include "UART.h"
/**************************************************************************************************************************/

void UART_init(MUART_Config_t *ptr_uart_config){

   /***************************************************************************************/
	MUART_UCSRA.BITS.Multi_Communication=0;

	MUART_UCSRA.BITS.Double_Speed=0;

	/***************************************************************************************/
	MUART_UCSRC =(MUART_UCSRC & 0xF9)  |( (ptr_uart_config ->dataBit) <<CHARACTER_SIZE_BIT);
	/* Operation1:
	 * clearing the bits responsible for the number of the data bits
	 *
	 * Operation2:
	 * insert the value dataBit  inside the register*/

	/************************(Testing)******************************/
	/* Operation1 is performed because
	 *
	 * IF any of the two bits responsible for the data was already set
	 * with a value 1 before initialization and IF you initialize it
	 *  with a value zero,
	 *  the value inserted in the register will be not be zero
	 * it will be one because it is an OR operation
	 */
	/**************************************************************/
	/**************************************************************************************/
	MUART_UCSRC= (MUART_UCSRC & 0xCF)|( (ptr_uart_config ->parityMode) <<PARITY_BIT);
	/* Operation1:
	 * clearing the bits responsible for the number of the PARITY bits
	 *
	 * Operation2:
	 * insert the value parityMode inside the register*/

	/************************(Testing)******************************/
	/* Operation1 is performed because
	 *
	 * IF any of the two bits responsible for the parity was already set
	 * with a value 1 before initialization and IF you initialize it
	 *  with a value zero,
	 *  the value inserted in the register will be not be zero
	 * it will be one because it is an OR operation
	 */
	/**************************************************************/
	/**************************************************************************************/
	MUART_UCSRC=(MUART_UCSRC & 0xF7) |((ptr_uart_config->stopBit)<<STOP_SELECT_BIT);
	/* Operation1:
	 * clearing the bits responsible for the number of the stop bits
	 *
	 * Operation2:
	 * insert the value stopBit inside the register*/

	/************************(Testing)******************************/
	/* Operation1 is performed because
	 *
	 * IF  the bit responsible for the stop bit was already set
	 * with a value 1 before initialization and IF you initialize it
	 *  with a value zero,
	 *  the value inserted in the register will be not be zero
	 * it will be one because it is an OR operation
	 */
	/**************************************************************/
	/**************************************************************************************/
	MUART_UCSRC= (MUART_UCSRC & 0xBF)|((ptr_uart_config->syncMode)<<USART_MODE_SELECT_BIT);
	/* Operation1:
	 * clearing the bits responsible for the number of the mode bits
	 *
	 * Operation2:
	 * insert the value syncModes inside the register*/

	/************************(Testing)******************************/
	/* Operation1 is performed because
	 *
	 * IF the bit responsible for the mode bit was already set
	 * with a value 1 before initialization and IF you initialize it
	 *  with a value zero,
	 *  the value inserted in the register will be not be zero
	 * it will be one because it is an OR operation
	 */
	/**************************************************************/
	SET_BIT (MUART_UCSRB,TRANSMITTER_ENABLE);
	SET_BIT (MUART_UCSRB,RECEIVER_ENABLE);

	/**************************************************************************************/
	/*Setting the low byte of baud rate*/
	MUART_UBRRL= (u8_t)(ptr_uart_config->baudRate);

	/*Setting the high byte of baud rate*/
	MUART_UBRRH = (u8_t)( (ptr_uart_config->baudRate) >> 8);

	/************************(Testing)******************************/
    /* The shift operation is done FIRST (ptr_uart_config->baudRate) >> 8
     * Then the cast operation (u8_t)(shifted value)
     *  OTHERWISE there will be a problem in the runtime
     */
	/**************************************************************/




}

/**************************************************************/
u8_t UART_ByteRecieved(void){

	while (MUART_UCSRA.BITS.Recevie_Complete == 1);

	return MUART_UDR;

}
/**************************************************************/
u8_t UART_IS_ByteRecieved(u8_t *ptr_data){

	u8_t status =0; /* Default value (nothing recieved) */

	if(MUART_UCSRA.BITS.Recevie_Complete == 1){

		*ptr_data= MUART_UDR;
		status=1;
	}

	return status;

}
/***********************************************************************************/
/*Difference between (UART_ByteRecieved) and (UART_IS_ByteRecieved):
 *
 * IN (UART_ByteRecieved) ---> the whole program waits till the byte is recieved
 * with the  POLLING METHOD
 *
 *  BUT WHAT IF: you need to check whether is something recevied or not and based on
 *  the status value you need to take a specific action
 *
 *  For example: if something is not recieved you will fire the alarm system
 *  so there is no need for the polling method here
 *  if used the polling method in that case the program will go through an infinite loop
 *  because nothing is recieved
 *  or wait for TOO LONG time so there is no need to waist that time instead
 *  (UART_IS_ByteRecieved) method is created
 */
/************************************************************************************/

void UART_SendByte(u8_t data){

	while (MUART_UCSRA.BITS.Data_Register_Empty==0);

	MUART_UDR= data;

}

/**********************************************************************************/
void UART_SendString(u8_t* str){

	u8_t index =0;

	while(str[index] != '\0'){

		UART_SendByte(str[index]);
		index++;
	}
}
/**********************************************************************************/
void UART_ReceiveString(u8_t* str){

	u8_t index =0;

	str[index] =UART_ByteRecieved();


	while(str[index] != '#')
	{
		index++;
		str[index] = UART_ByteRecieved();
	}


	str[index]='\0';

}
/**********************************( Testing )************************************************/
/*   Testing UART_ReceiveString function
 *
 *  Scenario1:
 *  IF that condition is not written str[index] =UART_ByteRecieved();
 *  the data will not be recieved correctly because the first byte will
 *  be equal to zero
 *
 * Scenario2:
 * IF  that line (str[index] = UART_recieveByte()) is swapped with that line index++;
 * there will be infinite loop because the condition will check on the next index
 * of the string which is empty so the condition of the while loop will
 * always be correct
 *
 *
 */
/*********************************************************************************************/



/*************************************************** PROTOCOLS  *************************************************************/
//void UART_SendString_CheckSum_Protocol(u8_t* str){

	//u8_t index=0;
	//u8_t lens=0;
	//u16_t sum;

	//while(str[lens] != '\0'){

		//sum+=str[lens];
		//lens++;
	//}

	//while(){

	//}

//}
/***********************************( Testing )*************************************************/
/*  Testing UART_SendString_CheckSum_Protocol
 *
 *  Scenario1:
 *  IF the two lines (sum+=str[lens]) and (lens++) are swapped the first element
 *  will not be added
 *
 *  Scenario2:
 *  IF the str is not a string and a normal array the while loop will go through an infinite loop
 *  because
 */
/**************************************( Description )*******************************************/
/*  Function UART_SendString_CheckSum_Protocol description
 *
 *
 */
/*********************************************************************************/
