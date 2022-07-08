
/****************************************************************************************************/
/* Name: timer_config.h                                                                             */
/* Author: Madonna Magdy                                                                             */
/* Version: V4                                                                                       */
/* Usage: This module contains the interfacing definition of  the timer peripheral configurations    */
/****************************************************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "lstd.h"
/**************************************  Enummeration  ***********************************************************************************/
/*Timer pre-scalers*/
typedef enum{
 MTIMER_NO_PRESCALING,
 MTIMER_PRESCALER_1,
 MTIMER_PRESCALER_8,
 MTIMER_PRESCALER_64,
 MTIMER_PRESCALER_256,
 MTIMER_PRESCALER_1024
}mtimerPrescaler_t;

typedef enum{
	Disable, Enable

}mimer_InterruptMask_State;

/**************************************   Delay Mode ***********************************************************************************/
typedef struct{
	mtimerPrescaler_t prescaler;
    u8_t CompareValue;


}DelayMode_8bit_Config_t;

typedef struct{
	mtimerPrescaler_t prescaler;
    u16_t CompareValue;

}DelayMode_16bit_Config_t;

/************************************** Creating instances of typedef Structure (Delay)*****************************************************************************************/
DelayMode_8bit_Config_t  delayTimer0_milli;

DelayMode_8bit_Config_t delayTimer0_micro;

DelayMode_8bit_Config_t  delayTimer2_milli;

DelayMode_8bit_Config_t delayTimer2_micro;

DelayMode_16bit_Config_t delayTimer1_minute;

DelayMode_16bit_Config_t delayTimer1_hour;


/**************************************   pwm Mode ***********************************************************************************/
typedef enum{
	 Normal_Operation =0xCF,    /* Normal port operation, OC0 disconnected */
	 NonInverting =0xEF,       /*Clear OC0 on compare match, set OC0 at BOTTOM*/
	 Inverting =0xFF           /* Set OC0 on compare match, clear OC0 at BOTTOM */

}PWM_compareOutputMode_t;

/***********************( Testing )********************************/
/* there is no need to create an enummeration for the non-PWM mode
 * because in the non-Pwm mode when there is an output Compare
 * there will be an interrupt. So, there is no need to make context
 * switching and waste time for that reason the output compare
 * mode in the config.h file is created for the pwm mode only
 * because the pwm mode does not give an interrupt
 * at the compare match
 */
 /*****************************************************************/

typedef struct{
	mtimerPrescaler_t prescaler;

	PWM_compareOutputMode_t compareOutputMode;

}PWM_8bit_Config_t;

/************************************** Creating instances of typedef Structure (pwm)*****************************************************************************************/
PWM_8bit_Config_t PWM_Timer0;
PWM_8bit_Config_t PWM_Timer2;


/************************************** ICU Mode *****************************************************************************************/
typedef enum{
	 FALLING, RISING

}icu_Edge_t;

typedef struct{

	icu_Edge_t edge;
	mtimerPrescaler_t prescaler;

} ICU_Config_t;
/************************************** Creating instances of typedef Structure (ICU)*****************************************************************************************/
ICU_Config_t   ICU_signalMeasurement;


#endif /* TIMER_CONFIG_H_ */
