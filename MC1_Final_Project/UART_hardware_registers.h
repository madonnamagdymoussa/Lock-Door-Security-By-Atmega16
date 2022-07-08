
#ifndef UART_HARDWARE_REGISTERS_H_
#define UART_HARDWARE_REGISTERS_H_

/**************************************************************************/
/*  A new type of Reg_8bit is created  for control register_A ONLY
 *  and NOT for control register_B or control register_C because we
 *  access the bits of register_B and register_C with the configuration data type
 *  defined in the files of UART_config.h and UART_config.c
 *  So, there is no benefit for creating a typedef union for these two registers
 *  or even making these registers with type Reg_8bit.
 *  it is NOT WRONG to make control A register or control B register
 *  with type Reg_8bit but the problem is that if you need to choose another mode for
 *  the UART you need to change it in the initialization function EVERY TIME ,
 *  but it is better to change it in the configuration file only and leave the
 *  initialization function as it is EVERY TIME we need to change the configuration(---> general method)
 *
 */
/**************************************************************************/
typedef union
{
	unsigned char Data;
	struct
	{
		unsigned char Multi_Communication:1;
		unsigned char Double_Speed:1;
		unsigned char Parity_Error:1;
		unsigned char Data_OverRun:1;
		unsigned char Frame_Error:1;
		unsigned char Data_Register_Empty:1;
		unsigned char Transmit_Complete:1;
		unsigned char Recevie_Complete:1;
	}BITS;
}Reg_8bit;
/*************************************************************************/

#define MUART_UDR      (*(volatile u8_t *const)(0x2C))
#define MUART_UCSRA    (*(volatile Reg_8bit *const)(0x2B))
#define MUART_UCSRB    (*(volatile u8_t *const)(0x2A))
#define MUART_UCSRC    (*(volatile u8_t *const)(0x40))
#define MUART_UBRRH    (*(volatile u8_t *const)(0x40))
#define MUART_UBRRL    (*(volatile u8_t *const)(0x29))
/**************************************************************************/


#endif /* UART_HARDWARE_REGISTERS_H_ */
