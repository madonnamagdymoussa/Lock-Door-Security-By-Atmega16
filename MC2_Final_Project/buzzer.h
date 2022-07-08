/*
 * buzzer.h
 *
 *  Created on: Nov 6, 2021
 *      Author: future
 */

#ifndef BUZZER_H_
#define BUZZER_H_



#include"mdio.h"

enum{
	Buzzer_Port = PORTB_ID,
	Buzzer_Pin = PIN0_ID

}Buzzer_config_t;

void Buzzer_init(void);

void Buzzer_ON(void);

#endif /* BUZZER_H_ */
