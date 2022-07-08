/*
 * open_door.h
 *
 *  Created on: Nov 5, 2021
 *      Author: future
 */

#ifndef OPEN_DOOR_H_
#define OPEN_DOOR_H_


void Enter_Password_MainPage(void);
void Display_Warning_MainPage(void);
void Open_Door_MainPage(void);
void Store_EEPROM_Password(void);
void Activate_Buzzer(void);
void Check_Entered_Password(void);
void Change_Password(void);
void Send_Password_MC2(void);

#endif /* OPEN_DOOR_H_ */
