/*
 * external_eeprom.h
 *
 *  Created on: Nov 4, 2021
 *      Author: future
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include"lstd.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

u8_t EEPROM_writeByte(u16_t u16addr, u8_t u8data);
u8_t EEPROM_readByte(u16_t u16addr, u8_t *u8data);



#endif /* EXTERNAL_EEPROM_H_ */
