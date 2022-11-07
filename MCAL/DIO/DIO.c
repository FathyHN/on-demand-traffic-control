/*
 * DIO.c
 *
 * Created: 10/7/2022 10:55:07 PM
 *  Author: Fat7y
 */ 
#include "DIO.h"

EN_dioError_t DIO_init(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioDDR_t direction) 
{
	switch (portNum)
	{
		case prtA:
			if(direction == OUT)
				SET_BIT(DDRA, pinNum);
			else if(direction == IN)
				CLR_BIT(DDRA,pinNum);
			else
				return WRONG_DDR;
			break;
		case prtB:
			if(direction == OUT)
				SET_BIT(DDRB, pinNum);
			else if(direction == IN)
				CLR_BIT(DDRB,pinNum);
			else
				return WRONG_DDR;
			break;
		case prtC:
			if(direction == OUT)
				SET_BIT(DDRC, pinNum);
			else if(direction == IN)
				CLR_BIT(DDRC,pinNum);
			else
				return WRONG_DDR;
			break;
		case prtD:
			if(direction == OUT)
				SET_BIT(DDRD, pinNum);
			else if(direction == IN)
				CLR_BIT(DDRD,pinNum);
			else
				return WRONG_DDR;
			break;
	}
	
	return OK_DIO;
}
EN_dioError_t DIO_Write(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioValue_t value)
{
	switch (portNum)
	{
		case prtA:
			if(value == HI)
				SET_BIT(PORTA, pinNum);
			else if(value == LO)
				CLR_BIT(PORTA,pinNum);
			else
				return WRONG_VAL;
			break;
		case prtB:
			if(value == HI)
				SET_BIT(PORTB, pinNum);
			else if(value == LO)
				CLR_BIT(PORTB,pinNum);
			else
				return WRONG_VAL;
			break;
		case prtC:
			if(value == HI)
				SET_BIT(PORTC, pinNum);
			else if(value == LO)
				CLR_BIT(PORTC,pinNum);
			else
				return WRONG_VAL;
			break;
		case prtD:
			if(value == HI)
				SET_BIT(PORTD, pinNum);
			else if(value == LO)
				CLR_BIT(PORTD,pinNum);
			else
				return WRONG_VAL;
			break;
		default:
			return PORTOVR;
	}
	
	return OK_DIO;
}
EN_dioError_t DIO_Read(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioValue_t *value)
{
	switch (portNum)
	{
		case prtA:
			*value = READ_BIT(PINA,pinNum);
			break;
		case prtB:
			*value = READ_BIT(PINB,pinNum);
			break;
		case prtC:
			*value = READ_BIT(PINC,pinNum);
			break;
		case prtD:
			*value = READ_BIT(PIND,pinNum);
		default:
			return PORTOVR;
	}
		
	return OK_DIO;
}
EN_dioError_t DIO_toggle(EN_dioPNum_t portNum, uint8_t pinNum)
{
	switch (portNum)
	{
		case prtA:
			TOGGLE_BIT(PORTA,pinNum);
			break;
		case prtB:
			TOGGLE_BIT(PORTB,pinNum);
			break;
		case prtC:
			TOGGLE_BIT(PORTC,pinNum);
			break;
		case prtD:
			TOGGLE_BIT(PORTD,pinNum);
		default:
			return PORTOVR;
	}
	
	return OK_DIO;
}