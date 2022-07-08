
#define F_CPU 8000000UL
#include"lstd.h"
#include "timer.h"
#include"lcd.h"
#include"UART.h"
#include"keypad.h"


#include "open_door.h"


extern u8_t gu8_option;



u8_t  IndexPassword;



int main(void){

	gu8_option =0;

	  DelayTimer_8bits_Init ( &delayTimer2_milli , TIMER2_INDEX_ARRAY);
	  DelayTimer_8bits_Init ( &delayTimer0_milli , TIMER0_INDEX_ARRAY);

	  OverflowTimer_16bits_Init(MTIMER_PRESCALER_1024);

	  UART_init(&MCU1);

	  LCD_init();

			for(;;){

				//LCD_displayStringRowColumn(0, 0, "+: Open Door");
				//LCD_displayStringRowColumn(1, 0, "-: Change Pass");

				//gu8_option = KEYPAD_getPressedKey(); /*get the chose option from user*/
				//DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);


				while( (gu8_option != '+') || (gu8_option != '-') ){


					//if( (gu8_option == 0) ){


						LCD_displayStringRowColumn(0, 0, "+: Open Door");
						LCD_displayStringRowColumn(1, 0, "-: Change Pass");

						gu8_option = KEYPAD_getPressedKey(); /*get the chose option from user*/
						DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);

					//}


			}/********************** End of while************************/


					while(gu8_option == '+'){

						Enter_Password_MainPage();
						Store_EEPROM_Password(); /*store the correct password automatically*/
                        Check_Entered_Password();/*check the entered maximum three times  */

						Open_Door_MainPage();
					}/********************** End of while(gu8_option == '+') ************************/


					while(gu8_option == '-'){

						LCD_displayStringRowColumn(0, 0, "Enter old");
						LCD_displayStringRowColumn(1, 0, "password");
						DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);

						Enter_Password_MainPage();
						Store_EEPROM_Password(); /*store the correct password automatically*/
                        Check_Entered_Password();/*check the entered maximum three times  */

                        Change_Password();
                        Send_Password_MC2(); /* send the new password to the mc2 to be stored in eeprom */

					}/********************** End of while(gu8_option == '-') ************************/




			}/********************** End of for loop ************************/

}/********************** End of main function ************************/





