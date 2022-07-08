/******************************************************************************************************/
/* Name: lcd.h                                                                                        */
/* Author: Madonna Magdy                                                                              */
/* Version: V3                                                                                        */
/* Usage: This module contains the interface definitions for the lcd driver                          */
/******************************************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include"lstd.h"
#include"mdio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

#if (LCD_DATA_BITS_MODE == 4)

/* if LCD_LAST_PORT_PINS is defined in the code, the LCD driver will use the last 4 pins in the gpio port for for data.
 * To use the first four pins in the gpio port for data just remove LCD_LAST_PORT_PINS */
#define LCD_LAST_PORT_PINS

#ifdef LCD_LAST_PORT_PINS
#define LCD_FIRST_DATA_PIN_ID         PIN4
#else
#define LCD_FIRST_DATA_PIN_ID         PIN0
#endif

#endif

/* LCD HW Ports and Pins Ids */
typedef enum{
	LCD_RS_PORT_ID   =  PORTD_ID,
	LCD_RW_PORT_ID   =  PORTD_ID,
	LCD_E_PORT_ID    =  PORTD_ID,
	LCD_DATA_PORT_ID =  PORTC_ID

}HardwarePortLCD_t;

typedef enum{
	LCD_RS_PIN_ID  =  PIN4_ID,

    LCD_RW_PIN_ID  =  PIN5_ID,

   LCD_E_PIN_ID   =  PIN6_ID


}HardwarePinLCD_t;


/* LCD Commands */
typedef enum{
 LCD_CLEAR_COMMAND   =            0x01,
 LCD_GO_TO_HOME     =             0x02,
 LCD_TWO_LINES_EIGHT_BITS_MODE =  0x38,
 LCD_TWO_LINES_FOUR_BITS_MODE =   0x28,
 LCD_CURSOR_OFF     =             0x0C,
 LCD_CURSOR_ON      =             0x0E,
 LCD_SET_CURSOR_LOCATION =        0x80

}LcdCommand_t;


void LCD_init(void);


void LCD_sendCommand(u8_t command);

void LCD_displayCharacter(u8_t data);


void LCD_displayString(const char *Str);


void LCD_moveCursor(u8_t row,u8_t col);


void LCD_displayStringRowColumn(u8_t row,u8_t col,const char *Str);


void LCD_intgerToString(int data);


void LCD_clearScreen(void);

#endif /* LCD_H_ */
