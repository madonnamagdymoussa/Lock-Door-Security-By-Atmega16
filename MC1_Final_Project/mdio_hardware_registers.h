
#ifndef MDIO_HARDWARE_REGISTERS_H_
#define MDIO_HARDWARE_REGISTERS_H_


/****************************GPIO PORT A********************************************************************************************************/
#define MDIO_PORTA    (*(volatile u8_t *const)(0x3B))
#define MDIO_DDRA     (*(volatile u8_t *const)(0x3A))
#define MDIO_PINA     (*(volatile const u8_t *const)(0x39))

/****************************GPIO PORT B********************************************************************************************************/
#define MDIO_PORTB    (*(volatile u8_t *const)(0x38))
#define MDIO_DDRB     (*(volatile u8_t *const)(0x37))
#define MDIO_PINB     (*(volatile const u8_t *const )(0x36))

/****************************GPIO PORT C********************************************************************************************************/
#define MDIO_PORTC    (*(volatile u8_t *const)(0x35))
#define MDIO_DDRC     (*(volatile u8_t *const)(0x34))
#define MDIO_PINC     (*(volatile const u8_t *const)(0x33))

/****************************GPIO PORT D********************************************************************************************************/
#define MDIO_PORTD    (*(volatile u8_t *const)(0x32))
#define MDIO_DDRD     (*(volatile u8_t *const)(0x31))
#define MDIO_PIND     (*(volatile const u8_t *const)(0x30))


#endif /* MDIO_HARDWARE_REGISTERS_H_ */
