
# include "mdio.h"
#include "timer.h"
#include "motor.h"

void static inline  DC_MOTOR_CLOCK_WISE(void){

	 mdio_setPinValue(PORTA_ID, PIN0_ID, DIO_HIGH_OUTPUT);  /* the output value of pin0  is 1 ---> INT1   */
	 mdio_setPinValue(PORTA_ID, PIN1_ID, DIO_LOW_OUTPUT);   /* the output value of pin1  is 0 ---> INT2   */

      }



void static inline  DC_MOTOR_ANTI_CLOCK_WISE(void){

	mdio_setPinValue(PORTA_ID, PIN0_ID, DIO_LOW_OUTPUT);/* the output value of pin0  is 0 ---> INT1  */
	mdio_setPinValue(PORTA_ID, PIN1_ID, DIO_HIGH_OUTPUT);/* the output value of pin1  is 1 ---> INT2   */

}




void static  DC_MOTOR_STOP(void){

	mdio_setPinValue(PORTA_ID,PIN0_ID, DIO_LOW_OUTPUT); /* the output value of pin0  is 0 ---> INT1  */
	mdio_setPinValue(PORTA_ID,PIN1_ID, DIO_LOW_OUTPUT);  /* the output value of pin1  is 0 ---> INT2   */


}

void DcMotor_Init(void){

	mdio_setPinStatus(PORTA_ID,PIN0_ID, DIO_OUTPUT_PIN);
	mdio_setPinStatus(PORTA_ID,PIN1_ID, DIO_OUTPUT_PIN); /* the micro-controller supply voltage or current  to l23D so
	                                                         the direction of pins will be output*/

	DC_MOTOR_STOP(); /*pointer to function for stopping the motor*/

	}



void DcMotor_Rotate(DcMotorState_t state)
{


    switch(state){

    case DC_CW:
    	DC_MOTOR_CLOCK_WISE();
    	OverflowTimer_16bits_Asynchrounous( _8_sec, DC_MOTOR_STOP);
    	break; /* break from this case */

   case DC_ACW:
	   DC_MOTOR_ANTI_CLOCK_WISE();
	   OverflowTimer_16bits_Asynchrounous( _8_sec, DC_MOTOR_STOP);
    	break;/* break from this case */

    case DC_STOP:
    	DC_MOTOR_STOP();
         break;/* break from this case */

        }

	 }

