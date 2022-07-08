
#include"i2c_hardware_register.h"
#include"lstd.h"
#include"i2c.h"
void TWI_init(TWI_Config_t *PTR_TWI){

	MTWI_TWSR = 0x00; /* clearing the register before inserting the pre-scaler value and the bit generator value  */
	MTWI_TWSR |= (PTR_TWI->Presacler); /* Insert the pre-scaling value */


	MTWI_TWBR |=(PTR_TWI->Bit_Rate_Generator); /* insert the bit generator value */


    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
	MTWI_TWAR = 0b00000010; // my address = 0x01 :)

	MTWI_TWCR.BITS.TWI_Enable =1;


}
/**************************************************************************************************/
void TWI_start(void){


	MTWI_TWCR.BITS.Interrupt_Flag=1;

	MTWI_TWCR.BITS.TWI_Enable =1;
	MTWI_TWCR.BITS.Start_Condition =1;


	/*********************( Testing )******************************/
	/*The rest of bits in the MTWI_TWCR register will be don't care
	 * So, there is no need to reset the register -->( MTWI_TWCR =0)
	 * as an initial step before those three lines of code
	 */
	/*********************( Testing )******************************/


while(0 == MTWI_TWCR.BITS.Interrupt_Flag);/*that flag is automatically cleared by hardware ,
	                                      so when it cleared by hardware --> termination of the process successfully
	                                      you need to check whether the process is terminated or not
	                                      in order to get out of this function*/

	/* the serial bus will be tested and the start condition will be generated after the bus becomes free*/
}
/****************************************************************************************************/
/*******************************************************************/
/* accesses to the  (TWAR), (TWSR), and (TWDR) will NOT BE allowed
 * UNLESS the flag is cleared by software
 *
 * New operation will NOT BE executed UNLESS the flag is cleared by software
 *
 * The enable pin is set if there is operation need to be executed
 * That operation could be :- Start , Stop , read , write , send data byte
 * or recieve data byte
 */
/*******************************************************************/

void TWI_stop(void){

	MTWI_TWCR.BITS.Interrupt_Flag=1;/*the operation will NOT BE executed UNLESS the flag is cleared by software */
	MTWI_TWCR.BITS.TWI_Enable =1;

	MTWI_TWCR.BITS.Stop_Condition=1;

}

void TWI_write(u8_t data){

	MTWI_TWCR.BITS.Interrupt_Flag=1;/*the operation will NOT BE executed UNLESS the flag is cleared by software */
	MTWI_TWCR.BITS.TWI_Enable =1; /*the operation of writing will be enabled*/

	MTWI_TWDR=data;
	/* accesses to the (TWDR) register will NOT BE allowed
     * UNLESS the flag is cleared by software*/

	while(0 == MTWI_TWCR.BITS.Interrupt_Flag);

}
/****************************************************************************************************/
u8_t TWI_readWithACK(void){

	MTWI_TWCR.BITS.Interrupt_Flag=1; /*the operation will NOT BE executed UNLESS the flag is cleared by software */
	MTWI_TWCR.BITS.TWI_Enable =1; /*the operation of reading will be enabled*/

	MTWI_TWCR.BITS.Enable_Acknowledge=1;
	/*Enable the feature of sending acknowledge from mater to slave
	 * when the master reads several bytes from slave */


	while(0 == MTWI_TWCR.BITS.Interrupt_Flag);/*that flag is automatically cleared by hardware ,
		                                      so when it cleared by hardware --> termination of the process successfully
		                                      you need to check whether the process is terminated or not
		                                      in order to get out of this function*/
	return MTWI_TWDR;

}
/****************************************************************************************************/
/**************************************************************************************************/
/*The NAK tells the slave transmitter to let go of control of the SDA line so
that the master can send a STOP. If the NAK was not sent, the slave
transmitter would try to send another byte (bit) while the master was trying
to send the STOP. The NAK lets the master take control of SDA to send the
STOP.*/
/**************************************************************************************************/
u8_t TWI_readWithNACK(void){

	MTWI_TWCR.BITS.Interrupt_Flag=1; /*the operation will NOT BE executed UNLESS the flag is cleared by software */
	MTWI_TWCR.BITS.TWI_Enable =1; /*the operation of reading will be enabled*/
	MTWI_TWCR.BITS.Enable_Acknowledge=0;

	while(0 == MTWI_TWCR.BITS.Interrupt_Flag);/*that flag is automatically cleared by hardware ,
		                                      so when it cleared by hardware --> termination of the process successfully
		                                      you need to check whether the process is terminated or not
		                                      in order to get out of this function*/

	return MTWI_TWDR;

}
/****************************************************************************************************/
u8_t TWI_getStatus(void)
{
    u8_t status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = MTWI_TWSR & 0xF8;
    return status;
}

