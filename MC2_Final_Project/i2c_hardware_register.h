
#ifndef I2C_HARDWARE_REGISTER_H_
#define I2C_HARDWARE_REGISTER_H_


/**************************************************************************/
typedef union
{
	unsigned char Data;
	struct
	{
		unsigned char Interrupt_Enable:1;
		unsigned char Reseved_bit:1;
		unsigned char TWI_Enable:1;
		unsigned char Write_Collision_Flag:1;
		unsigned char Stop_Condition:1;
		unsigned char Start_Condition:1;
		unsigned char Enable_Acknowledge:1;
		unsigned char Interrupt_Flag:1;
	}BITS;
}MTWI_TWCR_8bit_Reg;
/*************************************************************************/


/************************************************************************/
/*                            TWI Registers                             */
/************************************************************************/

#define MTWI_TWBR     (*(volatile u8_t *const)(0x20))
#define MTWI_TWSR     (*(volatile u8_t *const)(0x21))
#define MTWI_TWAR     (*(volatile u8_t *const)(0x22))
#define MTWI_TWDR     (*(volatile u8_t *const)(0x23))
#define MTWI_TWCR     (*(volatile MTWI_TWCR_8bit_Reg *const)(0x56))



#endif /* I2C_HARDWARE_REGISTER_H_ */
