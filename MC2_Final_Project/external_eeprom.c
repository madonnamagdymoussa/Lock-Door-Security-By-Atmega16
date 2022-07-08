/*
 * external_eeprom.c
 *
 *  Created on: Nov 4, 2021
 *      Author: future
 */


#include"i2c.h"
#include"external_eeprom.h"

u8_t EEPROM_writeByte(u16_t u16addr, u8_t u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
/*******************************************************************************/
/* First 8 bits are the location inside the memory the remaining 3 bits are
 * part of the device address which is the slave address
  */


    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
   TWI_write((u8_t) (0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
/*******************************************************************************/
    /* Send the required memory location address */
    TWI_write((u8_t)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
/*******************************************************************************/

    /* write byte to eeprom */
    TWI_write(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
/*******************************************************************************/

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;

}

u8_t EEPROM_readByte(u16_t u16addr, u8_t *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
    /*******************************************************************************/
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
    /*******************************************************************************/
    /* Send the required memory location address */
    TWI_write((u8_t)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
    /*******************************************************************************/
    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;
    /*******************************************************************************/
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;
    /*******************************************************************************/
    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;
    /*******************************************************************************/
    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
