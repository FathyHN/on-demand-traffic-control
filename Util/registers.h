/*
 * registers.h
 *
 * Created: 10/7/2022 10:54:13 PM
 *  Author: Fat7y
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "typedefs.h"
/************************************************************************/
/* DIO Registers                                                        */
/************************************************************************/
//Port A registers
#define PORTA (*(volatile uint8_t*)(0x3B))
#define DDRA  (*(volatile uint8_t*)(0x3A))
#define PINA  (*(volatile uint8_t*)(0x39))
//Port B registers
#define PORTB (*(volatile uint8_t*)(0x38))
#define DDRB  (*(volatile uint8_t*)(0x37))
#define PINB  (*(volatile uint8_t*)(0x36))
//Port C registers
#define PORTC (*(volatile uint8_t*)(0x35))
#define DDRC  (*(volatile uint8_t*)(0x34))
#define PINC  (*(volatile uint8_t*)(0x33))
//Port D registers
#define PORTD (*(volatile uint8_t*)(0x32))
#define DDRD  (*(volatile uint8_t*)(0x31))
#define PIND  (*(volatile uint8_t*)(0x30))

/************************************************************************/
/* Timers Registers                                                     */
/************************************************************************/
//Timer 0 registers
#define TCCR0 (*(volatile uint8_t*)(0x53))
#define TCNT0 (*(volatile uint8_t*)(0x52))
#define OCR0 (*(volatile uint8_t*)(0x5C))
#define TIMSK (*(volatile uint8_t*)(0x59))
#define TIFR (*(volatile uint8_t*)(0x58))

/************************************************************************/
/* Interrupts registers                                                 */
/************************************************************************/
#define SREG (*(volatile uint8_t*)(0x5F)) //Status register I-bit is number 7 in this register, you need to set it to enable global interrupt requests
#define MCUCR (*(volatile uint8_t*)(0x55)) //control interrupt sense for INT0 and INT1
#define MCUCSR (*(volatile uint8_t*)(0x54)) //control interrupt sense for INT2
#define GICR (*(volatile uint8_t*)(0x5B)) //enabling and disabling interrupts
#define GIFR (*(volatile uint8_t*)(0x5A)) //external Interrupts flag registers

#endif /* REGISTERS_H_ */