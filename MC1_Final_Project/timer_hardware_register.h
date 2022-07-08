


#ifndef TIMER_HARDWARE_REGISTER_H_
#define TIMER_HARDWARE_REGISTER_H_

/************************************************************************/
/*                            Timer Registers                           */
/************************************************************************/

/*Timer shared registers*/
#define MTIMER_SREG        (*(volatile u8_t* const)(0x5F))
#define MTIMER_TIMSK       (*(volatile u8_t* const)(0x59))
#define MTIMER_TIFR        (*(volatile u8_t* const)(0x58))

/*Timer0 registers*/
#define MTIMER_OCR0        (*(volatile u8_t* const)(0x5C))
#define MTIMER_TCCR0       (*(volatile u8_t* const)(0x53))
#define MTIMER_TCNT0       (*(volatile u8_t* const)(0x52))

/*Timer1 registers*/
#define MTIMER_TCCR1B       (*(volatile u8_t* const)(0x4E))
#define MTIMER_TCCR1A       (*(volatile u8_t* const)(0x4F))

#define MTIMER_TCNT1       (*(volatile u16_t* const)(0x4C))
#define MTIMER_OCR1A       (*(volatile u16_t* const)(0x4A))
#define MTIMER_OCR1B       (*(volatile u16_t* const)(0x48))
#define MTIMER_ICR1        (*(volatile u16_t* const)(0x46))

/*Timer2 registers*/
#define MTIMER_TCCR2       (*(volatile u8_t* const)(0x45))
#define MTIMER_TCNT2       (*(volatile u8_t* const)(0x44))
#define MTIMER_OCR2        (*(volatile u8_t* const)(0x43))

#endif /* TIMER_HARDWARE_REGISTER_H_ */
