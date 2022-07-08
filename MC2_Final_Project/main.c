#define F_CPU 8000000UL
#include"lstd.h"
#include"timer.h"
#include"UART.h"
#include"i2c.h"
#include"external_eeprom.h"
#include "motor.h"
#include "buzzer.h"

int main(void){

u8_t status;
//u8_t stored_pass;

u8_t password[5];
u8_t i;


  DelayTimer_8bits_Init ( &delayTimer2_milli , TIMER2_INDEX_ARRAY);
  DelayTimer_8bits_Init ( &delayTimer0_milli , TIMER0_INDEX_ARRAY);

  TWI_Config_t TWI1={
		  TWI_PRESCALER_1,
		  TWI_400k
  };

  TWI_init(&TWI1);

  UART_init(&MCU2);

  Global_Interrupt_Enable();

  Buzzer_init();

  DcMotor_Init();

  EEPROM_writeByte(0x0311,0xFF );

	for(;;){

		status=UART_ByteRecieved();


				        /*Receive the password and save it to the EEPROM*/
						if('A' == status){

							/*Receive password from MC1*/
							for(i = 0; i < 5; i++){
								password[i] = UART_ByteRecieved();
							}

							/*save data to EEPROM starting from address 0x0311*/
							for(i = 0; i < 5; i++){
								EEPROM_writeByte(0x0311, password[i]);
								DelayTimer_8bits_synchrounous( _10_milli_sec, TIMER2_INDEX_ARRAY);
							}
							status=0;
						}


						     if('B' == status){
						    	  Buzzer_ON();
						    	  status=0;
						     }


						        /*Send the saved password to MC1*/
								if('C' == status){

									for(i = 0; i < 5; i++){
										EEPROM_readByte(0x0311, &password[i]); /*read saved password from EEPROM*/
										DelayTimer_8bits_synchrounous( _10_milli_sec, TIMER2_INDEX_ARRAY);
									}

									for(i = 0; i < 5; i++){
										UART_SendByte(password[i]); /*send saved password to MC1*/
									}

									status = 0;
								}




								if('D' == status){

									DcMotor_Rotate(DC_CW);
									status = 0;
								}



	}
}
