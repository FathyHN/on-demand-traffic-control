/*
 * LED.c
 *
 * Created: 10/8/2022 1:56:13 AM
 *  Author: Fat7y
 */ 
#include <string.h>
#include "LED.h"
#include "../../MCAL/Timer/Timer.h"

EN_ledError_t LED_init(ST_LED_t* LED, EN_dioPNum_t prtNum, uint8_t pinNum, char color[]){
	DIO_init(prtNum, pinNum, OUT);
	strcpy((char*)(LED -> color), color);
	LED -> prtNum = prtNum;
	LED -> pinNum = pinNum;
	LED -> state = off;
	return LED_OK;
}
EN_ledError_t LED_on(ST_LED_t* LED){
	DIO_Write(LED->prtNum, LED->pinNum, HI);
	LED -> state = on;
	return LED_OK;
}
EN_ledError_t LED_off(ST_LED_t* LED){
	DIO_Write(LED->prtNum, LED->pinNum, LO);
	LED -> state = off;
	return LED_OK;
}
EN_ledError_t LED_toggle(ST_LED_t* LED){
	DIO_toggle(LED->prtNum, LED->pinNum);
	LED -> state = !(LED -> state);
	return LED_OK;
}

EN_ledError_t LED_blink(ST_LED_t** blinkingLEDs,uint8_t LEDsNO ,uint16_t frequency, uint8_t period)
{
	uint8_t blinks = frequency * period;
	float delay = 1000.0/(float)frequency;
	uint8_t i, j;
	for(i = 1; i <= blinks; i++ )
	{
		for(j = 0; j < LEDsNO; j++)
		LED_toggle(blinkingLEDs[j]);
		Timer_delay(delay);
	}
	return LED_OK;
}  