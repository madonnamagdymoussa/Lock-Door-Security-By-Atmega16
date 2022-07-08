/******************************************************************************************************/
/* Name: timer.h                                                                                      */
/* Author: Madonna Magdy                                                                              */
/* Version: V4                                                                                        */
/* Usage: This module contains the interface definitions for the timer peripheral                     */
/******************************************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_
/********************************************  Includes  ***************************************************************************/
#include "timer_config.h"

/*************************************  Callback Typedef *******************************************************************************************/
/*declaring a function pointer*/
typedef   void(*CallbackFunc_t)(void);
/*the typedef must take void and return void as the ISR is not callable so it is NOT ALLOWED that the user
 * insert a function argument */

/*************************************  Function RegisterCallback  *************************************************************************/
#define FUNC_REGISTER_SIZE 4

void RegisterCallback (u8_t function_id, CallbackFunc_t  p_callback_func );

/*************************************  Null pointer  *************************************************************/
#define NULL_PTR ( (void *) 0 )
/************************************* Macros for the index of array of functions*************************************************************/

#define TIMER0_OVF       (0)    /* Index zero in ---> func_register_8bit_overflow[]  */
#define TIMER2_OVF       (1)     /* Index one in ---> func_register_8bit_overflow[]  */

#define TIMER0_COMP      (0)    /* Index zero in ---> func_register_8bit_compare[]  */
#define TIMER2_COMP      (1)     /* Index one in ---> func_register_8bit_compare[]  */

#define TIMER1_OVF       (0)       /* Index zero in ---> func_register_16bit_timer1[]  */
#define TIMER1_COMPA     (1)       /* Index one in ---> func_register_16bit_timer1[]  */
#define TIMER1_COMPB     (2)       /* Index two in ---> func_register_16bit_timer1[]  */
#define TIMER1_CAPT      (3)       /* Index three in ---> func_register_16bit_timer1[]  */

/************************************* Timer Counter Control Register(0)*************************************************************/
#define TCCR_CLOCK_SELECT_0        (0)
#define TCCR_CLOCK_SELECT_1        (1)
#define TCCR_CLOCK_SELECT_2        (2)
#define TCCR_WAVE_GENERATION_CTC   (3)
#define TCCR_COMPARE_MATCH_0       (4)
#define TCCR_COMPARE_MATCH_1       (5)
#define TCCR_WAVE_GENERATION_PWM   (6)
#define TCCR0_FORCE_OUTPUT_COMPARE (7)

/*************************************Timer Counter Control Register(1A) *************************************************************/
#define TCCR1A_WAVE_GENERATION_PWM10         (0)
#define TCCR1A_WAVE_GENERATION_PWM11         (1)
#define TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELB (2)
#define TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA (3)
#define TCCR1A_COMPARE_OUTPUT_CHANNELB0      (4)
#define TCCR1A_COMPARE_OUTPUT_CHANNELB1      (5)
#define TCCR1A_COMPARE_OUTPUT_CHANNELA0      (6)
#define TCCR1A_COMPARE_OUTPUT_CHANNELA1      (7)

/*************************************Timer Counter Control Register(1B)*************************************************************/
#define TCCR1B_CLOCK_SELECT_10             (0)
#define TCCR1B_CLOCK_SELECT_11             (1)
#define TCCR1B_CLOCK_SELECT_12             (2)
#define TCCR1B_WAVE_GENERATION_12          (3)
#define TCCR1B_WAVE_GENERATION_13          (4)
#define TCCR1B_Input_Capture_Edge_Select   (6)

/************************************* Timer Interrupt Mask Register *****************************************************************/
#define OVERFLOW_INTERRUPT_ENABLE0               (0)
#define OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE0   (1)

#define OVERFLOW_INTERRUPT_ENABLE1               (2)
#define OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE_1A (4)

#define OVERFLOW_INTERRUPT_ENABLE2               (6)
#define OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE2   (7)
/*************************************Timer Counter Control Register2 *************************************************************/
#define TCCR2_CLOCK_SELECT_20        (0)
#define TCCR2_CLOCK_SELECT_21        (1)
#define TCCR2_CLOCK_SELECT_22        (2)
#define TCCR2_WAVE_GENERATION_21     (3)
#define TCCR2_COMPARE_OUTPUT_20      (4)
#define TCCR2_COMPARE_OUTPUT_21      (5)
#define TCCR2_WAVE_GENERATION_20     (6)
#define TCCR2_FORCE_OUTPUT_COMPARE   (7)
/***********************************************************************************************************************/
#define TIMER0_INDEX_ARRAY           (0)
#define TIMER2_INDEX_ARRAY           (1)
/**************************************************Timer interrupt flag register *********************************************************************/
#define TIMER0_OUTPUT_COMPARE_FLAG             (1)
#define TIMER1_OVERFLOW_FLAG                   (2)
#define TIMER1_OUTPUT_COMPARE_FLAG_1A          (4)
#define TIMER2_OUTPUT_COMPARE_FLAG             (7)
/***********************************************************************************************************************/
#define _1_milli_sec                  (1)
#define _10_milli_sec                 (10)
#define _500_milli_sec               (500)
#define _10_micro_sec                (10)
#define _8_sec                        (1)
#define _1_minute                    (7)
/****************************************************************************************************************************************/
/* FunctionID    : DelayTimer_8bits_Init
 *
 * Description : This function is responsible for initializing the timer with the delay mode
 * based on the configuration defined in the timer_config file
 * This function is for TIMER0 and TIMER2 as it is 8BIT_configurations
 *
 *
 *PRE_CONDITION: the peripheral must be setup with the configurations
 *PRE_CONDITION: the timerIndex value must be TIMER0_INDEX_ARRAY or TIMER2_INDEX_ARRAY
 *
 *POST_CONDITION:the timer selected based on the index and configurations will be initialized
 *
 *
 * INPUT:ptr_delayTimer a pointer to 8bit configuration
 * INPUT: timerIndex (value that will be inserted in the index of the array)
 * Return: void
 *
 * */
void  DelayTimer_8bits_Init ( DelayMode_8bit_Config_t * ptr_delayTimer , u8_t timerIndex);
/****************************************************************************************************************************************/
/* FunctionID    : DelayTimer_8bits_synchrounous
 *
 * Description : This function is responsible for making the delay (with polling method --> synchronous )
 *This function is for TIMER0 and TIMER2 as it is 8BIT_configurations
 *
 *PRE_CONDITION: the timer must be initialized with (DelayTimer_8bits_Init) function
 *PRE_CONDITION: the timerIndex value must be TIMER0_INDEX_ARRAY or TIMER2_INDEX_ARRAY
 *PRE_CONDITION: the au8_delayTime value will be with in a rage of (1---> 256)
 *
 *POST_CONDITION: the delay required will be executed and finished (synchronous)
 *
 *INPUT: au8_delayTime
 * Return: void
 *
 * */

void  DelayTimer_8bits_synchrounous(u16_t au8_delayTime,u8_t timerIndex);
/****************************************************************************************************************************************/
/* FunctionID    : RegisterCallback
 *
 * Description : This function is responsible for registering the address of the API function
 *  in the HAL or the application to the address of the function that is in the ISR
 *
 *PRE_CONDITION: the address points to a function that function must take void and must return void
 *PRE_CONDITION: the function_id must be within a range of (0 ---> 7)
 *PRE_CONDITION: the pointer to function inside the ISR must be initialized with a null value
 *
 *POST_CONDITION: the pointer to function that is inside the isr function will be pointing to p_callback_func
 *
 *INPUT: function_id (index of the array)
 *INPUT: p_callback_func
 * Return: void
 *
 * */
//void RegisterCallback (u8_t function_id, CallbackFunc_t  p_callback_func );

void  DelayTimer_8bits_Asynchrounous(u8_t timerIndex, u8_t au8_delayTime, CallbackFunc_t p_callback_func);
void  DelayTimer_8bits_synchrounous(u16_t au8_delayTime,u8_t timerIndex);
void OverflowTimer_16bits_Init(mtimerPrescaler_t Prescaler);
void  OverflowTimer_16bits_Asynchrounous(u8_t Number_OverFlows, CallbackFunc_t  p_callback_func);
void  OverflowTimer_16bits_synchrounous(u8_t NumberOverFlows_sync);
void Global_Interrupt_Enable(void);

/************************************* ICU  Function prototypes  ***********************************************************************************/

void  Icu_init( ICU_Config_t * ptr_icu_config); /* initializing the icu driver  */

void  Icu_setEdgeDetectionType( icu_Edge_t edge); /* setting the requird edge that the interrupt will occur based on*/

 u16_t  Icu_getInputCaptureValue(void);  /* getting the value of a specified count of time (in TCNT register)
                                            and at a specified edge and storing it in the ICR1 register */

 void Icu_DeInit(void);/* STOPPING the icu driver by clearing the values of the timer1 register */

 void  Icu_clearTimerValue(void); /* clear the value of the timer counter  */

/************************************* Call back  Function prototypes  ***********************************************************************************/
 void RegisterCallback_8Bit_Overflow(u8_t function_id, CallbackFunc_t  p_callback_func );

 void RegisterCallback_8Bit_Compare(u8_t function_id, CallbackFunc_t  p_callback_func );

 void RegisterCallback_16Bit_Timer1(u8_t function_id, CallbackFunc_t  p_callback_func );

#endif /* TIMER_H_ */
