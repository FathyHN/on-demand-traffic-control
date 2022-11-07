/*
 * LED.h
 *
 * Created: 10/8/2022 1:55:48 AM
 *  Author: Fat7y
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/interrupts/interrupts.h"
#include <stdarg.h>

typedef enum EN_ledError_t
{
	LED_OK, LED_notFound
}EN_ledError_t;
typedef enum EN_ledState_t
{
	off, on
}EN_ledState_t;

typedef struct ST_LED_t{
	uint8_t color[7];
	EN_ledState_t state;
	EN_dioPNum_t prtNum;
	uint8_t pinNum;
	}ST_LED_t;

EN_ledError_t LED_init(ST_LED_t* LED, EN_dioPNum_t prtNum, uint8_t pinNum, char color[]);
EN_ledError_t LED_on(ST_LED_t* LED);
EN_ledError_t LED_off(ST_LED_t* LED);
EN_ledError_t LED_toggle(ST_LED_t* LED);

#endif /* LED_H_ */