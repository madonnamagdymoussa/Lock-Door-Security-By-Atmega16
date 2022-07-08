/******************************************************************************************************/
/* Name   : lcd.c                                                                                     */
/* Author : Madonna Magdy                                                                             */
/* Version: V3                                                                                        */
/* Usage  : This module contains the implementation for the lcd driver functions                      */
/******************************************************************************************************/


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/

#include"mdio.h"
#include"lstd.h"
#include"timer.h" /*for delay functions*/
#include"lcd.h"
#include <stdlib.h> /*for itoa function*/
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/




/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */


void LCD_init(void)
{
	DelayTimer_8bits_Init ( &delayTimer0_milli , TIMER0_INDEX_ARRAY);

	/* Configure the direction for RS, RW and E pins as output pins */
	mdio_setPinStatus(LCD_RS_PORT_ID,LCD_RS_PIN_ID,DIO_OUTPUT_PIN);
	mdio_setPinStatus(LCD_RW_PORT_ID,LCD_RW_PIN_ID,DIO_OUTPUT_PIN);
	mdio_setPinStatus(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_OUTPUT_PIN);

#if (LCD_DATA_BITS_MODE == 4)

	/* Configure 4 pins in the data port as output pins */
	mdio_setPinStatus(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID,DIO_OUTPUT_PIN);
	mdio_setPinStatus(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+1,DIO_OUTPUT_PIN);
	mdio_setPinStatus(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+2,DIO_OUTPUT_PIN);
	mdio_setPinStatus(LCD_DATA_PORT_ID,LCD_FIRST_DATA_PIN_ID+3,DIO_OUTPUT_PIN);

	LCD_sendCommand(LCD_GO_TO_HOME);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */

#elif (LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	 GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	 LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(u8_t command)
{
	//u8_t lcd_port_value = 0;
	mdio_setPinValue(LCD_RS_PORT_ID,LCD_RS_PIN_ID,DIO_LOW_OUTPUT); /* Instruction Mode RS=0 */
	mdio_setPinValue(LCD_RW_PORT_ID,LCD_RW_PIN_ID,DIO_LOW_OUTPUT); /* write data to LCD so RW=0 */

	/*
	What really matters is that all these signals must be stable for a minimum or a maximum period of time.
	For example lines RS and R/W must be stable for a minimum period of time
	before level logic on the 'E' line is raised to a logic 1.*/


	DelayTimer_8bits_synchrounous( _1_milli_sec, TIMER0_INDEX_ARRAY);


	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_HIGH_OUTPUT); /* Enable LCD E=1 */

		/* before setting the data lines to their logic levels the enable pin must be high for
		 * minimum time of 190ns to stabilize the signal to
		 *ensure that Enable signal is high before reading the data signal
		 *NOTE ---> the enable pin must be high in order to read and send the data signal to the buffer
		 *The equation for calculating that time Tpw - Tdws */

	DelayTimer_8bits_synchrounous( _1_milli_sec, TIMER0_INDEX_ARRAY);

#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (command & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((command & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tdsw = 100ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Th = 13ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_HIGH_OUTPUT); /* Enable LCD E=1 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required command to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((command & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (command & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tdsw = 100ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID,command); /* out the required command to the data bus D0 --> D7 */
	 /* delay for processing Tdsw = 100ns */
	DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY);

	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	 /* delay for processing Th = 13ns */
	DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY );
#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(u8_t data)
{
	//u8_t lcd_port_value = 0;
	mdio_setPinValue(LCD_RS_PORT_ID,LCD_RS_PIN_ID,DIO_HIGH_OUTPUT); /* Data Mode RS=1 */
	mdio_setPinValue(LCD_RW_PORT_ID,LCD_RW_PIN_ID,DIO_LOW_OUTPUT); /* write data to LCD so RW=0 */

	 /* delay for processing Tas = 50ns */
	 DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY);

	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_HIGH_OUTPUT); /* Enable LCD E=1 */
	/* delay for processing Tpw - Tdws = 190ns */
	 DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY);

#if (LCD_DATA_BITS_MODE == 4)
	/* out the last 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | (data & 0xF0);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | ((data & 0xF0) >> 4);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tdsw = 100ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Th = 13ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_HIGH_OUTPUT); /* Enable LCD E=1 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the first 4 bits of the required data to the data bus D4 --> D7 */
	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS
	lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F) << 4);
#else
	lcd_port_value = (lcd_port_value & 0xF0) | (data & 0x0F);
#endif
	GPIO_writePort(LCD_DATA_PORT_ID,lcd_port_value);

	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Tdsw = 100ns */
	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	mtimer_delayMs_sync(MTIMER_CHANNEL_1, 1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	 GPIO_writePort(LCD_DATA_PORT_ID,data); /* out the required data to the data bus D0 --> D7 */

	/* delay for processing Tdsw = 100ns */
	 DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY);

	mdio_setPinValue(LCD_E_PORT_ID,LCD_E_PIN_ID,DIO_LOW_OUTPUT); /* Disable LCD E=0 */
	/* delay for processing Th = 13ns */
	 DelayTimer_8bits_synchrounous( _1_milli_sec,TIMER0_INDEX_ARRAY);
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	u8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	*********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(u8_t row,u8_t col)
{
	u8_t lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(u8_t row,u8_t col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}


