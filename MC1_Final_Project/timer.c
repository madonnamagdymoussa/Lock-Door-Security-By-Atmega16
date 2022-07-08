/*************************************************************************************************************************************/
/* Name: timer.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                            */
/* Version: V4                                                                                                                      */
/* Usage: This module contains the implementation for the timer functions                                                */
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/* Testing ID description:
 * first number of testing signifies the module used (the timer module takes number1)
 *
 * The second number signifies that whether you are testing a function or an array or a variable
 * (The variable takes number1 ,The array takes number 2, The function takes number 3  )
 *
 * The Third number signifies the the ID of a function or an array or a variable
 *
 * The fourth number signifies how many number of tests you use on a certain variable or function or a variable
 */
/*************************************************************************************************************************************/

/*************************************************************************************************************************************/
/* ID Description:

 * The First number signifies that whether you are testing a function or an array or a variable
 * (The variable takes number1 ,The array takes number 2, The function takes number 3  )
 *
 * The Second number signifies the the ID of a function or an array or a variable
 */
/*************************************************************************************************************************************/


/********************************************  Includes  ***************************************************************************/
#include "lbit.h"
#include "lstd.h"

/***********************************/
#include "timer_hardware_register.h"
#include "timer.h"

/***********************************/
#include <avr/interrupt.h>
/***********************************/
#include "mdio.h"
/******************************************** Timer global variables  *******************************************************************/

/*Global variable used to hold the selected timer1 pre-scaler*/
static u8_t gu8_timer_16bits_SelectedPrescaler1=0; /* ID  = 1.1  */

static u8_t gu8_timer_8bits_SelectedPrescaler[2]={0}; /* ID=2.1  */

/************************************* (Testing 1.1.1.1 ) *************************************/
/************************************* (Testing 1.2.1.1 ) *************************************/

/*It is not preferable to start the timer at the initialization function
 * once there is a selected pre-scaler inserted in the timer control register the timer will start counting
 * It is more preferable to have a function for starting the timer and for stopping the timer
 * so the value of the selected  pre-scaler will be copied into a global variable that hold the value of the pre-scaler
 * the global variable that hold the selected pre-scaler will be inserted into the timer counter control register in the
 * function of start timing and stop timing
 *
 */
/***********************************************************************************/
static u8_t gu8_delayTime[2]={0}; /* ID =2.2 */
//static u8_t gu8_overflowTime =0;  /* ID =1.1 */
static u8_t Number_OverFlows_16bit_Timer =0; /* ID =1.10 */

/*Global variables to set the delay time for timer0 or timer2  according to the index inserted
 *that delay time will be used in the isr*/
/***********************************************************************************/

/************************************ID =1.2 *********************/
 //static volatile u8_t DelayTimer_timer0_synchrounous_is_Running =0;

 /************************************ID =1.3 *********************/
 static volatile u8_t DelayTimer_timer0_Asynchrounous_is_Running =0;

 /************************************ID =1.4 *********************/
 //static volatile u8_t OverflowTimer_timer0_synchrounous_is_Running =0;

 /************************************ID =1.5 *********************/
 static volatile u8_t OverflowTimer_timer0_Asynchrounous_is_Running =0;


/************************************* (Testing 1.1.2.1 ) *************************************/
 /************************************* (Testing 1.1.3.1 ) *************************************/
 /************************************* (Testing 1.1.4.1 ) *************************************/
 /************************************* (Testing 1.1.5.1 ) *************************************/
  /* variables with IDs 1.3 and 1.5 is used for checking that when timer 0
   * is counting time using  asynchrounous operation It is forbidden that the user use
   * the delay mode or the pwm mode unless the  asynchrounous operation is terminated
   *
   */
 /**********************************************************************************************/

 /************************************ID =1.6 *********************/
  //static volatile u8_t DelayTimer_timer2_synchrounous_is_Running =0;

  /************************************ID =1.7 *********************/
  static volatile u8_t DelayTimer_timer2_Asynchrounous_is_Running =0;

  /************************************ID =1.8 *********************/
  //static volatile u8_t OverflowTimer_timer2_synchrounous_is_Running =0;

  /************************************ID =1.9 *********************/
  static volatile u8_t OverflowTimer_timer2_Asynchrounous_is_Running =0;

  /************************************* (Testing 1.1.6.1 ) *************************************/
   /************************************* (Testing 1.1.7.1 ) *************************************/
   /************************************* (Testing 1.1.8.1 ) *************************************/
   /************************************* (Testing 1.1.9.1 ) *************************************/
  /* variables with IDs 1.7 and 1.9 is used for checking that when timer 2
   * is counting time using  asynchrounous operation It is forbidden that the user use
   * the delay mode or the pwm mode unless the  asynchrounous operation is terminated
   *
   */
  /**********************************************************************************************/





/******************************************** Call Back Function ********************************************************************/

/* An array of functions handlers each with an id.*/
/* Without the curly braces in {NULL_PTR} , the FIRST callback function ONLY  will be initialized with null pointer*/

/*********************************** ID =2.3 ******************************/
static volatile  CallbackFunc_t func_register_8bit_overflow[2] = {NULL_PTR};

/*********************************** ID =2.4 ******************************/
static volatile  CallbackFunc_t func_register_8bit_compare[2] =  {NULL_PTR};

/*********************************** ID =2.5 ******************************/
static volatile  CallbackFunc_t func_register_16bit_timer1[4] =  {NULL_PTR};



/******************************************* ID =2.6****************************************/
u8_t TIMER_OUTPUT_COMPARE_FLAG_BIT[2]={TIMER0_OUTPUT_COMPARE_FLAG,TIMER2_OUTPUT_COMPARE_FLAG};
/*array that holds the number of bits of flag register of timer0 and timer2 in the interrupt flag mask register */

/******************************************* ID =2.7****************************************/
u8_t TIMER_INTERRUPT_OVERFLOW_ENABLE_BIT[2]={OVERFLOW_INTERRUPT_ENABLE0,OVERFLOW_INTERRUPT_ENABLE2};
/*array that holds the number of bits of timer interrupt mask register ---> overflow interrupt enable bits in timer0 and timer2 */

/******************************************* ID =2.8****************************************/
u8_t TIMER_INTERRUPT_COMPARE_ENABLE_BIT[2]={OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE0,OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE2};
/*array that holds the number of bits of timer interrupt mask register ---> compare interrupt enable bits in timer0 and timer2 */

/******************************************** Array Of pointers to Registers *******************************************************************/


/**************************************************************************************************************/
/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

/************************ ID =2.9***************************/
static volatile u8_t *const Timer_8bits_Control_Register[2]={
		(u8_t*)(&MTIMER_TCCR0),
		(u8_t*)(&MTIMER_TCCR2),


};

/*********************************(Testing 1.2.9.1 )********************/
/* The array of pointers to registers should be static
 * The number of pointers to registers should be equal to the number of 8 bit timers
 * The pointer itself should be constant because the location of the register is constant
 * Casting should be performed --> (u8_t*)
 */
/*********************************(Testing 1.2.9.1 )********************/
/**************************************************************************************************************/
/**************************************************************************************************************/


/**************************************************************************************************************/
/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

/************************ ID =2.10***************************/
static volatile u8_t *const Timer_8bits_Compare_Match_Register[2]={
		(u8_t*)(&MTIMER_OCR0),
		(u8_t*)(&MTIMER_OCR2)


};

/*********************************(Testing 1.2.10.1 )********************/
/* The array of pointers to registers should be static
 * The number of pointers to registers should be equal to the number of 8 bit timers
 * The pointer itself should be constant because the location of the register is constant
 * Casting should be performed --> (u8_t*)
 */
/*********************************(Testing 1.2.10.1 )********************/
/**************************************************************************************************************/
/**************************************************************************************************************/



/**************************************************************************************************************/
/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

/************************ ID =2.11***************************/
static volatile u8_t *const Timer_8bits_Counter_Register[2]={
		(u8_t*)(&MTIMER_TCNT0),
		(u8_t*)(&MTIMER_TCNT2)

};

/*********************************(Testing 1.2.11.1 )********************/
/* The array of pointers to registers should be static
 * The number of pointers to registers should be equal to the number of 8 bit timers
 * The pointer itself should be constant because the location of the register is constant
 * Casting should be performed --> (u8_t*)
 */
/**************************************************************************************************************/
/**************************************************************************************************************/


/***************************************** Static Functions ******************************************************************************************/

/********************************************  8BIT TIMER  ********************************************************************/

/************************** ID =3.1 ******************************/
void static inline mtimer_8bits_start(u8_t timerIndex)
{

	/*Resetting the selected timer counter*/
    *Timer_8bits_Counter_Register[timerIndex]= 0;

	/*Clear the bits responsible for the clock selection of the selected timer*/
	*Timer_8bits_Control_Register[timerIndex] &= ~(1<<TCCR_CLOCK_SELECT_0) & ~(1<<TCCR_CLOCK_SELECT_1) & ~(1<<TCCR_CLOCK_SELECT_2);

	/*Adding the previous selected timer pre-scaler*/
	 *Timer_8bits_Control_Register[timerIndex] |= gu8_timer_8bits_SelectedPrescaler[timerIndex];

	 return;

}

/************************** ID =3.2 ******************************/
void static inline mtimer_8bits_stop(u8_t timerIndex)
{
	/*Clear the bits responsible for the clock selection*/
	*Timer_8bits_Control_Register[timerIndex] &= ~(1<<TCCR_CLOCK_SELECT_0) & ~(1<<TCCR_CLOCK_SELECT_1) & ~(1<<TCCR_CLOCK_SELECT_2);

	/*Return from this function*/
	return;
}

/************************** ID =3.3 ******************************/
void static inline mtimer_16bits_start(void){

	/*Resetting timer counter1*/
	MTIMER_TCNT1 =0;

	MTIMER_TCCR1B &= ~(TCCR1B_CLOCK_SELECT_10) & ~(TCCR1B_CLOCK_SELECT_11) & ~(TCCR1B_CLOCK_SELECT_12);

	MTIMER_TCCR1B |= gu8_timer_16bits_SelectedPrescaler1;

}

/************************** ID =3.4 ******************************/
void static inline mtimer_16bits_stop(void){
	MTIMER_TCCR1B &= ~(TCCR1B_CLOCK_SELECT_10) & ~(TCCR1B_CLOCK_SELECT_11) & ~(TCCR1B_CLOCK_SELECT_12);

}


/************************************* (Testing 1.3.1.1) *************************************/
/************************************* (Testing 1.3.2.1) *************************************/
/************************************* (Testing 1.3.3.1) *************************************/
/************************************* (Testing 1.3.4.1) *************************************/
/*There is no need to make context switching and waist time of the overhead so the function is inline
 * the function is static because it is not called outside the timer.c file
 */
/*************************************************************************************/



/********************************************  ISR  ***************************************************************************/

/************************** ID =3.5 ******************************/
ISR(TIMER0_OVF_vect){
	  	if(func_register_8bit_overflow[TIMER0_OVF] != NULL_PTR){

	  		/*Checking of the delay time expired or not*/
	  		if(gu8_delayTime[TIMER0_INDEX_ARRAY]--){

	  			/*Do nothing */
	  		}

	  		else{

	  			mtimer_8bits_stop(TIMER0_INDEX_ARRAY);
	  			OverflowTimer_timer0_Asynchrounous_is_Running=0;

	  		   func_register_8bit_overflow[TIMER0_OVF]();



	  		}

	}
}
/****************************************************/

/************************** ID =3.6 ******************************/
ISR(TIMER2_OVF_vect){
	if(func_register_8bit_overflow[TIMER2_OVF] != NULL_PTR){

		/*Checking of the delay time expired or not*/
			  		if(gu8_delayTime[TIMER2_INDEX_ARRAY]--){

			  			/*Do nothing */
			  		}


	else{
		        mtimer_8bits_stop(TIMER2_INDEX_ARRAY);
		        OverflowTimer_timer2_Asynchrounous_is_Running=0;

		  		func_register_8bit_overflow[TIMER2_OVF]();




		  		}
}
}
/****************************************************/
/****************************************************/
/****************************************************/

/************************** ID =3.7 ******************************/
ISR(TIMER0_COMP_vect){
	if(func_register_8bit_compare[TIMER0_COMP] != NULL_PTR){

				/*Checking of the delay time expired or not*/
				  		if(gu8_delayTime[TIMER0_INDEX_ARRAY]--){

				  			/*Do nothing */
				  		}

		else{

     		mtimer_8bits_stop(TIMER0_INDEX_ARRAY);
			DelayTimer_timer0_Asynchrounous_is_Running= 0;


		   func_register_8bit_compare[TIMER0_COMP]();

	}


  }
}
/****************************************************/

/************************** ID =3.8 ******************************/
ISR(TIMER2_COMP_vect){
 	if(func_register_8bit_compare[TIMER2_COMP] != NULL_PTR){

 		/*Checking of the delay time expired or not*/
 						  		if(gu8_delayTime[TIMER2_INDEX_ARRAY]--){

 						  			/*Do nothing */
 						  		}

 			else{
 		 		mtimer_8bits_stop(TIMER2_INDEX_ARRAY);
 		 		DelayTimer_timer2_Asynchrounous_is_Running= 0;


 		        func_register_8bit_compare[TIMER2_COMP]();

 		}

 	}
 }
/****************************************************/
/****************************************************/
/****************************************************/
/************************** ID =3.9 ******************************/
ISR(TIMER1_OVF_vect){
	if(func_register_16bit_timer1[TIMER1_OVF] != NULL_PTR){

		if (Number_OverFlows_16bit_Timer --){
             /* Do nothing  */
		}

		else{
			mtimer_16bits_stop();

		func_register_16bit_timer1[TIMER1_OVF]();


		}

	}
}
/****************************************************/

/************************** ID =3.10 ******************************/
ISR(TIMER1_COMPA_vect){
	if(func_register_16bit_timer1[TIMER1_COMPA] != NULL_PTR){

		if(Number_OverFlows_16bit_Timer --){

		}

		else{
			mtimer_16bits_stop();
		    func_register_16bit_timer1[TIMER1_COMPA]();


		}

	}
}
/****************************************************/

/************************** ID =3.11 ******************************/
ISR(TIMER1_COMPB_vect){
	if(func_register_16bit_timer1[TIMER1_COMPB] != NULL_PTR){

		mtimer_16bits_stop();
		func_register_16bit_timer1[TIMER1_COMPB]();


	}
	  }
/****************************************************/
/************************** ID =3.12 ******************************/
ISR(TIMER1_CAPT_vect){
	if(func_register_16bit_timer1[TIMER1_CAPT] != NULL_PTR){

		mtimer_16bits_stop();
		func_register_16bit_timer1[TIMER1_CAPT]();


	}

}

/************************************* (Testing 1.3.5.1) *************************************/
/************************************* (Testing 1.3.6.1) *************************************/
/************************************* (Testing 1.3.7.1) *************************************/
/************************************* (Testing 1.3.8.1) *************************************/
/************************************* (Testing 1.3.9.1) *************************************/
/************************************* (Testing 1.3.10.1) *************************************/
/************************************* (Testing 1.3.11.1) *************************************/
/************************************* (Testing 1.3.12.1) *************************************/
/* If you don't initialize func_register[] with a null pointer
* and you forgot to register the call back function there will
* be segmentation fault because you are trying to access a wild pointer */

/* The advantage of the if condition ---> (if(func_register[] != NULL_PTR) )
* you can't check on a garbage value but you can check on the null value
* to see if the pointer to function (func_register[]) doesn't hold the
* address of a function or doesn't hold a value*/
/***********************************************************************************/


/************************************* (Testing 1.3.5.2) *************************************/
/************************************* (Testing 1.3.6.2) *************************************/
/************************************* (Testing 1.3.7.2) *************************************/
/************************************* (Testing 1.3.8.2) *************************************/
/************************************* (Testing 1.3.9.2) *************************************/
/************************************* (Testing 1.3.10.2) *************************************/
/************************************* (Testing 1.3.11.2) *************************************/
/************************************* (Testing 1.3.12.2) *************************************/
/*
 * IF your application gives the interrupt periodically during the whole time when the program is running
 * then the function  mtimer_16bits_stop() or mtimer_8bits_stop() should NOT be inserted in the ISR function
 */
/*************************************************************************************/


/************************************* (Testing 1.3.5.3) *************************************/
/************************************* (Testing 1.3.6.3) *************************************/
/************************************* (Testing 1.3.7.3) *************************************/
/************************************* (Testing 1.3.8.3) *************************************/
/************************************* (Testing 1.3.9.3) *************************************/
/************************************* (Testing 1.3.10.3) *************************************/
/************************************* (Testing 1.3.11.3) *************************************/
/************************************* (Testing 1.3.12.3) *************************************/
/* In ISR function if you need to close the timer then it must be done before the callback function
 *  in order to let other drivers use it if they need
 *
 * IF the timer is not closed before the call back function and another driver use that timer
 * the timer will be started  by that driver and IF the call back function is finished
 * while the other driver is using  the timer , the timer will be stopped while other driver is using it
 */
/*************************************************************************************/



/****************************************************************************************************************************************/
/********************************************  DELAY MODE *******************************************************************************/
/****************************************************************************************************************************************/


/********************************************  8BIT TIMER  ********************************************************************/
/* the user have the option to select between timer0 and timer2 for initializing the delay function
 * by using the timerIndex  which is an index of the array of pointers to registers */

/************************** ID =3.13 ******************************/
void  DelayTimer_8bits_Init ( DelayMode_8bit_Config_t * ptr_delayTimer , u8_t timerIndex){

	 *Timer_8bits_Control_Register[timerIndex] |= (1<<TCCR_WAVE_GENERATION_CTC);
	 *Timer_8bits_Control_Register[timerIndex] &= ~(1<< TCCR_WAVE_GENERATION_PWM);
	 /* Clear bit 6 and set bit 3 in timer control register 0 OR timer control register 2
	  * according to the index inserted */


	  gu8_timer_8bits_SelectedPrescaler[timerIndex]  = (ptr_delayTimer->prescaler);

	 *Timer_8bits_Compare_Match_Register[timerIndex] =(ptr_delayTimer->CompareValue);

	 *Timer_8bits_Control_Register[timerIndex] &=~(TCCR_COMPARE_MATCH_0) &~(TCCR_COMPARE_MATCH_1);
		/* No need to connect the OC0 in the overflow and the delay mode
	       it will be connected in the PWM mode because in the delay mode
	       it will not give an interrupt every time there is a compare match  */


}
/********************************************  8BIT TIMER  ********************************************************************/
/************************** ID =3.14 ******************************/
void  DelayTimer_8bits_synchrounous(u16_t au8_delayTime,u8_t timerIndex){

/***************************************************************************************************************/

	//if ( 0 == timerIndex ){

		//if(  ( 1== DelayTimer_timer0_Asynchrounous_is_Running)   || (1==OverflowTimer_timer0_Asynchrounous_is_Running)){
			//while( ( 1== DelayTimer_timer0_Asynchrounous_is_Running)  || (1==OverflowTimer_timer0_Asynchrounous_is_Running));
		//}

		//}

		//if ( 2 == timerIndex ){

			//if( ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running)){
					//while( ( 1== DelayTimer_timer2_Asynchrounous_is_Running) || (1==OverflowTimer_timer2_Asynchrounous_is_Running));
				//}


				//}
/***************************************************************************************************************/

	 mtimer_8bits_start(timerIndex); /* pre-scaling value inserted */

	/*Looping over the time */
	 while(au8_delayTime--){

		 while( 0 == GET_BIT(MTIMER_TIFR,TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]) );

		 /*Clearing the OCF0 flag*/
		 SET_BIT(MTIMER_TIFR, TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]);

	 }

	 mtimer_8bits_stop(timerIndex); /* pre-scaling value cleared*/


}
/********************************************  8BIT TIMER  ********************************************************************/
/************************** ID =3.15 ******************************/
void  DelayTimer_8bits_Asynchrounous(u8_t timerIndex, u8_t au8_delayTime, CallbackFunc_t p_callback_func){

	/***************************************************************************************************************/

		//if ( 0 == timerIndex ){

			//if(   ( 1== DelayTimer_timer0_Asynchrounous_is_Running)  || (1==OverflowTimer_timer0_Asynchrounous_is_Running)){
				//while( ( 1== DelayTimer_timer0_Asynchrounous_is_Running)  || (1==OverflowTimer_timer0_Asynchrounous_is_Running));
			//}

			//else{
				//DelayTimer_timer0_Asynchrounous_is_Running= 1;
			//}

			//}

			//if ( 2 == timerIndex ){

				//if( ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running)){
						//while(  ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running));
					//}

					//else{
						//DelayTimer_timer2_Asynchrounous_is_Running= 1;

					//}

					//}
	/***************************************************************************************************************/



	mtimer_8bits_start(timerIndex); /* pre-scaling value inserted */

	gu8_delayTime[2]= au8_delayTime;

	func_register_8bit_compare[timerIndex]=p_callback_func;
	/* register the callback function to be executed in the ISR
	 * when the interrupt occurs  */

	SET_BIT(MTIMER_TIMSK,TIMER_INTERRUPT_COMPARE_ENABLE_BIT[timerIndex]);


}

/**************************************************************************/
/* In synchrounous function the 8bit timer is stopped inside the function after the
 * delay occurs
 *
 * In Asynchrounous function the 8bit timer is stopped NOT inside the function
 * but INSIDE the ISR block after the func_register_8bit_compare[timerIndex]() is executed
 */
/*************************************************************************************/






/****************************************************************************************************************************************/
/********************************************  NORMAL MODE *******************************************************************************/
/****************************************************************************************************************************************/

/************************** ID =3.16 ******************************/
void  OverflowTimer_8bits_Init(u8_t timerIndex, mtimerPrescaler_t Prescaler ){

	*Timer_8bits_Control_Register[timerIndex] &= ~(1<< TCCR_WAVE_GENERATION_PWM) & ~(1<<TCCR_WAVE_GENERATION_CTC);
      /* Clear bit 6 and bit 3 in timer control register 0 OR timer control register 2
       * according to the index inserted */

	gu8_timer_8bits_SelectedPrescaler[timerIndex]= Prescaler;
	/* don't start the timer now
	 * so, you can store that value in a global variable
	 * to use it in the synchrounous or the Asynchrounous function*/


	*Timer_8bits_Control_Register[timerIndex] &=~(TCCR_COMPARE_MATCH_0) &~(TCCR_COMPARE_MATCH_1);
	/* No need to connect the OC0 in the overflow and the delay mode
       it will be connected in the PWM mode because in the delay mode
       it will not give an interrupt every time there is a compare match  */

}
/********************************************  8BIT TIMER  ********************************************************************/

/************************** ID =3.17 ******************************/
void  OverflowTimer_8bits_synchrounous(u8_t Number_OverFlows,u8_t timerIndex){

	/***************************************************************************************************************/

		//if ( 0 == timerIndex ){

			//if(  ( 1== DelayTimer_timer0_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer0_Asynchrounous_is_Running)){
				//while( ( 1== DelayTimer_timer0_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer0_Asynchrounous_is_Running));
			//}


			//}

			//if ( 2 == timerIndex ){

				//if(  ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running)){
						//while(  ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running));
					//}


					//}
	/***************************************************************************************************************/


	mtimer_8bits_start(timerIndex);
	/* pre-scaling value inserted
	 in timer0 OR timer2 register
	 according to the index inserted*/


	while(Number_OverFlows--){

	while( 0 == GET_BIT(MTIMER_TIFR,TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]) );

	 /*Clearing the OCF0 flag*/
	 SET_BIT(MTIMER_TIFR, TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]);
	}

	mtimer_8bits_stop(timerIndex);
	/* pre-scaling value cleared
	 * in timer0 OR timer2 register
	 according to the index inserted*/


}
/********************************************  8BIT TIMER  ********************************************************************/

/************************** ID =3.18 ******************************/
void  OverflowTimer_8bits_Asynchrounous(u8_t timerIndex, u8_t au8_delayTime, CallbackFunc_t  p_callback_func){


	/***************************************************************************************************************/

		//if ( 0 == timerIndex ){

			//if(  ( 1== DelayTimer_timer0_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer0_Asynchrounous_is_Running)){
				//while( ( 1== DelayTimer_timer0_Asynchrounous_is_Running)  || (1==OverflowTimer_timer0_Asynchrounous_is_Running));
			//}

			//else{
				//OverflowTimer_timer0_Asynchrounous_is_Running= 1;
			//}

			//}

			//if ( 2 == timerIndex ){

				//if( ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running)){
						//while( ( 1== DelayTimer_timer2_Asynchrounous_is_Running) ||  (1==OverflowTimer_timer2_Asynchrounous_is_Running));
					//}

					//else{
						//OverflowTimer_timer2_Asynchrounous_is_Running= 1;

					//}

					//}
	/***************************************************************************************************************/



	mtimer_8bits_start(timerIndex);
	/* pre-scaling value inserted
	 in timer0 OR timer2 register
	 according to the index inserted*/

	gu8_delayTime[2]= au8_delayTime;

	func_register_8bit_overflow[timerIndex]=p_callback_func;
	/* register the callback function to be executed in the ISR
	 * when the interrupt occurs  */

	SET_BIT(MTIMER_TIMSK,TIMER_INTERRUPT_OVERFLOW_ENABLE_BIT[timerIndex]);


}
/********************************************  8BIT TIMER  ********************************************************************/


/********************************************  16BIT TIMER  ********************************************************************/

/************************** ID =3.19 ******************************/
void OverflowTimer_16bits_Init(mtimerPrescaler_t Prescaler){


	 MTIMER_TCCR1A &= ~(TCCR1A_WAVE_GENERATION_PWM10) & ~(TCCR1A_WAVE_GENERATION_PWM11);

	 MTIMER_TCCR1B |= (TCCR1B_WAVE_GENERATION_12);
	 MTIMER_TCCR1B &= ~(TCCR1B_WAVE_GENERATION_13);

	 gu8_timer_16bits_SelectedPrescaler1= Prescaler;
    /* insert the pre-scaler value in a global variable   */

	 MTIMER_TCCR1A &= ~(TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA);
	 /* non-pwm modes  */

	 MTIMER_TCCR1A &= ~(1<<TCCR1A_COMPARE_OUTPUT_CHANNELA1) & ~(TCCR1A_COMPARE_OUTPUT_CHANNELA0);
	 /* No need to connect the OC1A in the overflow and the delay mode
	  it will be connected in the PWM mode because in the delay mode
	  it will not give an interrupt every time there is a compare match  */

 }



 /*************************************************************************/
 /* In synchrounous function the 8bit timer is stopped inside the function after the
  * delay occurs
  *
  * In Asynchrounous function the 8bit timer is stopped NOT inside the function
  * but INSIDE the ISR block after the func_register_8bit_overflow[timerIndex]() is executed
  */
 /****************************************************************************************/
/************************** ID =3.20 ******************************/
void  OverflowTimer_16bits_Asynchrounous(u8_t Number_OverFlows, CallbackFunc_t  p_callback_func){

	 mtimer_16bits_start();

	 Number_OverFlows_16bit_Timer = Number_OverFlows;

	 func_register_16bit_timer1[TIMER1_OVF] = p_callback_func;

	 SET_BIT(MTIMER_TIMSK,OVERFLOW_INTERRUPT_ENABLE1);

 }
/************************** ID =3.21 ******************************/
 void  OverflowTimer_16bits_synchrounous(u8_t NumberOverFlows_sync){

	 mtimer_16bits_start();

	 while(NumberOverFlows_sync--){
			  while( 0 == GET_BIT(MTIMER_TIFR,TIMER1_OVERFLOW_FLAG));

			  SET_BIT(MTIMER_TIFR,TIMER1_OVERFLOW_FLAG);
		 }

	 mtimer_16bits_stop();
 }

 void Global_Interrupt_Enable(void){
	 SET_BIT(MTIMER_SREG,7);
 }

 void Disable_Interrupt_Enable(void){
	 CLEAR_BIT(MTIMER_SREG,7);
 }

/****************************************************************************************************************************************/
/********************************************  PWM MODE *******************************************************************************/
/****************************************************************************************************************************************/

/********************************************  8BIT TIMER  ********************************************************************/
//void  PWMTimer_8bit_Init(u8_t timerIndex){


	//mdio_setPinStatus(PORTB_ID, PIN3_ID, DIO_OUTPUT_PIN);
   // mdio_setPinValue(PORTB_ID, PIN3_ID, DIO_HIGH_OUTPUT);

   // *Timer_8bits_Control_Register[timerIndex] |= (1<<TCCR_WAVE_GENERATION_CTC)|(1<<TCCR_WAVE_GENERATION_PWM);

//}
/*************************************************************************************************************************/

/********************************************  16BIT TIMER  ********************************************************************/







/****************************************************************************************************************/
/********************************************  ICU MODE *********************************************************/
/****************************************************************************************************************/

/****************************************************************************************************************/
void  Icu_init( ICU_Config_t * ptr_icu_config){

      /* NORMAL MODE the timer counts till 65,536  */
	  MTIMER_TCCR1A |= (TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELB)|(TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA) ;

	  MTIMER_TCCR1B = ( (MTIMER_TCCR1B & 0xF8)|  (ptr_icu_config ->prescaler));

	  MTIMER_TCCR1B = ( (MTIMER_TCCR1B & 0xBF)|  ((ptr_icu_config->edge)<<TCCR1B_Input_Capture_Edge_Select) );
	  /* Insert the required edge and pre-scaling  */

	  MTIMER_TCNT1 = 0;

	  MTIMER_ICR1=0;

	  /* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	  MTIMER_TIMSK |=(1<<5);

	  MTIMER_SREG=(1<<7);

}
/****************************************************************************************************************/
void  Icu_setEdgeDetectionType( icu_Edge_t edge){

	MTIMER_TCCR1B =( (MTIMER_TCCR1B & 0xBF) | ( edge << TCCR1B_Input_Capture_Edge_Select ) );
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
}
/****************************************************************************************************************/
 u16_t  Icu_getInputCaptureValue(void){

	 return MTIMER_ICR1;

}
/******************************************** STOPPING ICU DRIVER  ********************************************************************/
void Icu_DeInit(void){

	MTIMER_TCCR1A=0;
	MTIMER_TCCR1B=0;

	MTIMER_TCNT1=0;
	MTIMER_OCR1A=0;
	MTIMER_OCR1B=0;
	MTIMER_ICR1=0;

	MTIMER_TIMSK=(0<<5);
/* clear  the bit responsible for the interrupt enable */
	/* Disable the icu driver  */
}

/****************************************************************************************************************/
 void  Icu_clearTimerValue(void){
	 MTIMER_TCNT1=0;
}

/***********************************************************************************************************************/

 void RegisterCallback_8Bit_Overflow(u8_t function_id, CallbackFunc_t  p_callback_func ) {

	 func_register_8bit_overflow[function_id] = p_callback_func;
  }
/* insert the required callback function in the pointer to function --> func_register_8bit_overflow[function_id]    */


 void RegisterCallback_8Bit_Compare(u8_t function_id, CallbackFunc_t  p_callback_func ) {

	 func_register_8bit_compare[function_id] = p_callback_func;
  }
/* insert the required callback function in the pointer to function --> func_register_8bit_compare[function_id]   */


 void RegisterCallback_16Bit_Timer1(u8_t function_id, CallbackFunc_t  p_callback_func ) {

	 func_register_16bit_timer1[function_id] = p_callback_func;
  }
/* insert the required callback function in the pointer to function --> func_register_16bit_timer1[function_id]    */

