
#ifndef I2C_H_
#define I2C_H_

#include "lstd.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */


typedef enum{

	TWI_PRESCALER_1 = 0, //clearing bit 0 and bit 1
	TWI_PRESCALER_4 = 1, //setting bit 0 and clearing bit 1
	TWI_PRESCALER_16 = 2, //clearing bit 0 and setting bit 1
	TWI_PRESCALER_64 = 3 //setting bit 0 and bit 1

}TWI_Bit_Rate_Presacler;

/* SCL frequency = CPU Clock frequency/16 + 2(TWBR)*/

typedef enum{
	TWI_500k = 0x00,
	TWI_400k = 0x02,
	TWI_250k = 0x08

}TWI_Bit_Rate_Generator_Prescaler0;

typedef struct {
	TWI_Bit_Rate_Presacler Presacler;

	TWI_Bit_Rate_Generator_Prescaler0 Bit_Rate_Generator;
}TWI_Config_t;

//TWI_Config_t TWI1;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(TWI_Config_t *PTR_TWI);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(u8_t data);
u8_t TWI_readByteWithACK(void);
u8_t TWI_readWithNACK(void);
u8_t TWI_getStatus(void);


#endif /* I2C_H_ */
