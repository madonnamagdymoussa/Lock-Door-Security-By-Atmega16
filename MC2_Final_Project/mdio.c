/*************************************************************************************************************************************/
/* Name: mdio.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                            */
/* Version: V3                                                                                                                      */
/* Usage: This module contains the implementation for the mdio functions                                                 */
/*************************************************************************************************************************************/

/********************************  Includes  *******************************************************************************************/
#include"lbit.h"
#include "lstd.h"
/*************************************/
#include "mdio_hardware_registers.h"
#include "mdio.h"
/*************************************/
//#include<assert.h>
//#include<stdlib.h>

/********************************  static Module variable definition  *******************************************************************************************/

/*  Creating a 2D array of Pointers to access the needed register
 *  the first dimension is for the port needed
 *  and the second dimension is for the register needed  */

/* NOTE ---->  the user is not allowed to call that array of pointer
 * he/she is only allowed to call the functions declared in the dio.h file
 * the user is not concerned with the hardware implementations
 * so the keyword static is added */

 volatile static u8_t * const  DIO_PORT_REG[NUM_PORTS][NUM_DIO_REGISTER] = {

{(u8_t *)&MDIO_DDRA , (u8_t *)&MDIO_PORTA , (u8_t *)&MDIO_PINA},
{(u8_t *)&MDIO_DDRB , (u8_t *)&MDIO_PORTB , (u8_t *)&MDIO_PINB},
{(u8_t *)&MDIO_DDRC , (u8_t *)&MDIO_PORTC , (u8_t *)&MDIO_PINC},
{(u8_t *)&MDIO_DDRD , (u8_t *)&MDIO_PORTD , (u8_t *)&MDIO_PIND}

};

/**************************************************************************************************************************************/
 void  mdio_setPinStatus(DioPort_t au8_port, DioChannel_t au8_pin, DioPinState_t au8_status){

    //assert((au8_port>=MIN_NUM_PORT) && (au8_port <= MAX_NUM_PORT));
   // assert((au8_pin >= MIN_NUM_PIN) && (au8_pin  <= MAX_NUM_PIN));
   // assert((au8_status >= DIO_MIN_STATE_VALUE) && (au8_status <= DIO_MAX_STATE_VALUE));


	switch(au8_status){

	    case DIO_OUTPUT_PIN:

		      SET_BIT(*DIO_PORT_REG[au8_port][DDR],(au8_pin));  /*accessing the DDR register of a specific port */
		       break; /* break from the DIO_OUTPUT_PIN  case */  /* example --> *DIO_PORT_REG[PORTA][DDR]  */

	    case DIO_INPUT_FLOAT_PIN:

	    	 CLEAR_BIT(*DIO_PORT_REG[au8_port][DDR],(au8_pin));  /*accessing the DDR register of a specific port*/
	    	  break;/* break from the DIO_INPUT_FLOAT_PIN case  */


	    case DIO_INPUT_PULLUP_PIN:

	    	CLEAR_BIT(*DIO_PORT_REG[au8_port][DDR],(au8_pin) ); /*accessing the DDR register of a specific port*/
			SET_BIT(*DIO_PORT_REG[au8_port][PORT],(au8_pin)) ;  /*accessing the PORT register of a specific port*/
             break; /* break from the DIO_INPUT_PULLUP_PIN case*/
	}
	  return;
}
/**************************************************************************************************************************************/


/**************************************************************************************************************************************/
void  mdio_setPinValue(DioPort_t au8_port, DioChannel_t au8_pin, DioOutputValue_t au8_value){

	//assert((au8_port>=MIN_NUM_PORT) && (au8_port <= MAX_NUM_PORT));
	//assert((au8_pin >= MIN_NUM_PIN) && (au8_pin  <= MAX_NUM_PIN));
    //assert((au8_value == DIO_HIGH)||(au8_value == DIO_LOW));

	switch(au8_value){

	case DIO_LOW_OUTPUT:
		CLEAR_BIT(*DIO_PORT_REG[au8_port][PORT],(au8_pin)) ;
		break; /* break from the DIO_LOW_OUTPUT case*/

	case DIO_HIGH_OUTPUT:
		SET_BIT(*DIO_PORT_REG[au8_port][PORT],(au8_pin)) ;
		break; /* break from the DIO_HIGH_OUTPUT case*/
	}
	return;
}

/**************************************************************************************************************************************/


/**************************************************************************************************************************************/
void  mdio_togglePinValue(DioPort_t au8_port, DioChannel_t au8_pin){

	//assert((au8_port>=MIN_NUM_PORT) && (au8_port <= MAX_NUM_PORT));
	//assert((au8_pin >= MIN_NUM_PIN) && (au8_pin  <= MAX_NUM_PIN));

	TOGGLE_BIT(*DIO_PORT_REG[au8_port][PORT],(au8_pin));
	return;
}
/**************************************************************************************************************************************/


/**************************************************************************************************************************************/
u8_t  mdio_getPinValue(DioPort_t au8_port, DioChannel_t au8_pin){

	//assert((au8_port>=MIN_NUM_PORT) && (au8_port <= MAX_NUM_PORT));
	//assert((au8_pin >= MIN_NUM_PIN) && (au8_pin  <= MAX_NUM_PIN));

	u8_t value=0;


		if(GET_BIT(*DIO_PORT_REG[au8_port][PORT],(au8_pin))){


		value=DIO_HIGH_OUTPUT;
		}

		else{

		value=DIO_LOW_OUTPUT;
		}

	return value;
}
/**************************************************************************************************************************************/



/**************************************************************************************************************************************/
void GPIO_setupPortDirection(DioPort_t au8_port, GPIO_PortDirectionType au8_direction){

	*DIO_PORT_REG[au8_port][DDR]=au8_direction;

}
/**************************************************************************************************************************************/




/**************************************************************************************************************************************/
void GPIO_writePort(u8_t au8_port, u8_t au8_value){

	*DIO_PORT_REG[au8_port][PORT]=au8_value;

}

/**************************************************************************************************************************************/




/**************************************************************************************************************************************/
u8_t  GPIO_readPort(u8_t au8_port){

	u8_t au8_value = DIO_LOW_OUTPUT;

	au8_value=*DIO_PORT_REG[au8_port][PIN];

	return  au8_value;

}
/**************************************************************************************************************************************/

