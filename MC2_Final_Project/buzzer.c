/*
 * buzzer.c
 *
 *  Created on: Nov 6, 2021
 *      Author: future
 */


#include "buzzer.h"
#include"timer.h"

void Buzzer_init(void){

	 mdio_setPinStatus(Buzzer_Port, Buzzer_Pin, DIO_OUTPUT_PIN);
	 mdio_setPinValue(Buzzer_Port, Buzzer_Pin, DIO_LOW_OUTPUT);

}

void static  Buzzer_OFF(void){

	mdio_setPinValue(Buzzer_Port, Buzzer_Pin, DIO_LOW_OUTPUT);
}

void Buzzer_ON(void){

	mdio_setPinValue(Buzzer_Port, Buzzer_Pin, DIO_LOW_OUTPUT);
	OverflowTimer_16bits_Asynchrounous( _1_minute, Buzzer_OFF);
}


