/*
 * open_door.c
 *
 *  Created on: Nov 5, 2021
 *      Author: future
 */
#include "timer.h"
#include "lcd.h"
#include "keypad.h"
#include "UART.h"

#include "open_door.h"


u8_t gu8_option =0;

u8_t  checkPass[5];
u8_t  checkPass_Changed[5];

u8_t passCount = 0;
u8_t i = 0;
u8_t thief =0;

u8_t Num_pass_Entered_Wrong;

u8_t storedPassEEPROM[5];

/*if the user choose open door option*/
void Enter_Password_MainPage(void){

	i=0;
	passCount=0;


	LCD_clearScreen(); /*clear screen*/
	LCD_displayStringRowColumn(0, 0, "Enter password:");
	DelayTimer_8bits_synchrounous( _10_milli_sec, TIMER2_INDEX_ARRAY);

	LCD_moveCursor(1,0);


	while(passCount < 5){

	  if(KEYPAD_getPressedKey()){

		checkPass[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);
		i++;
		passCount++;
	}

	   }


}


 void Display_Warning_MainPage(void){

	LCD_clearScreen();
	LCD_displayStringRowColumn(1, 0, "Not Matching");

	thief++;
	DelayTimer_8bits_synchrounous( _1000_milli_sec, TIMER2_INDEX_ARRAY);




}


void Open_Door_MainPage(void){

	if((0 == thief) || (1 == thief) || (2 == thief) ){

	LCD_clearScreen();
	LCD_displayString("Correct Pass");
	LCD_displayStringRowColumn(1, 0, "Open Door");

	UART_SendByte('D'); /*send to MC2 signal to open door*/

	OverflowTimer_16bits_synchrounous( _8_sec );

	 passCount = 0;
	 i = 0;
	 thief =0;
	 gu8_option =0;

	}


}

void Activate_Buzzer(void){

	LCD_clearScreen(); /*clear screen*/

	LCD_displayStringRowColumn(0, 0, "ERROR");
	LCD_displayStringRowColumn(1, 0, "Buzzer On");

	OverflowTimer_16bits_synchrounous( _1_minute );  // wait 1 minute until the buzzer stops

	LCD_clearScreen(); /*clear screen*/

	 passCount = 0;
	 i = 0;
	 thief =0;
	 gu8_option =0;



}

void Store_EEPROM_Password(void){

	UART_SendByte('C'); /*tell MC2 to send the saved password*/

	for(i = 0; i < 5; i++){
		(storedPassEEPROM[i] = UART_ByteRecieved());

	}

}

void Check_Entered_Password(void){

	   for(Num_pass_Entered_Wrong=0 ; Num_pass_Entered_Wrong<4;Num_pass_Entered_Wrong++){

			for(i = 0; i < 5; i++){ /* loop over number of characters  */

			if(checkPass[i] != storedPassEEPROM[i]){
					Display_Warning_MainPage();
					break; /*break from the for loop and go to the if condition ( 3 == thief)*/
				}/********************** End of if ************************/


			}/********************** End of for loop  --> for(i = 0; i < 5; i++) ************************/
			if ( 3 == thief){
				    UART_SendByte('B');/*send signal to MC2 to activate buzzer*/
					Activate_Buzzer();

					}
			if( 4 == i ){
				return; /* get out from the function if password is entered correctly*/
			}

			Enter_Password_MainPage();


		}/********************** End of for loop ************************/



}


 void static Store_Password_Again(void){

	i=0;
	passCount=0;


	LCD_clearScreen(); /*clear screen*/
	LCD_displayStringRowColumn(0, 0, "RE-Enter pass:");
	LCD_moveCursor(1,0);


	while(passCount < 5){
	if(KEYPAD_getPressedKey()){
	checkPass_Changed[i] = KEYPAD_getPressedKey();
	LCD_displayCharacter('*');
	DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);

	i++;
	passCount++;
	  }
		}

 }


 void Change_Password(void){

	  if((0 == thief) || (1 == thief) || (2 == thief) ){

		  LCD_clearScreen();
		  LCD_displayStringRowColumn(0, 0, "Enter new");
		  LCD_displayStringRowColumn(1, 0, "Password");
		  DelayTimer_8bits_synchrounous( _1000_milli_sec, TIMER2_INDEX_ARRAY);

		  Enter_Password_MainPage(); //first time password entered will be stored in checkPass[]

		  Store_Password_Again();


		  while(checkPass_Changed[i] !=  checkPass[i]){

				LCD_clearScreen(); /*clear screen*/
				LCD_displayStringRowColumn(0, 0, "Not Matching");
				DelayTimer_8bits_synchrounous( _500_milli_sec, TIMER2_INDEX_ARRAY);

				Enter_Password_MainPage();
				Store_Password_Again();

			}

	  }

  }


 void Send_Password_MC2(void){

	 UART_SendByte('A'); /*send a signal to MC2 to save the next sent data*/

		/*Send the password to MC2 to save it to EEPROM*/
		for(i = 0; i < 5; i++){

			UART_SendByte(checkPass_Changed[i]); /*send password to MC2 to save it in EEPROM*/
		}

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Saved");
		DelayTimer_8bits_synchrounous( _1000_milli_sec, TIMER2_INDEX_ARRAY);


 }
