/*
 * abb.c
 *
 * Created: 10/13/2022 12:23:24 PM
 *  Author: Fat7y
 */ 

#include "abb.h"

void transition(uint8_t frequency, uint8_t period)
{
	uint8_t blinks = frequency * period;
	float delay = 1000.0/(float)frequency;
	while(blinks != 0)
	{
		LED_toggle(&ledCarYellow);
		LED_toggle(&ledPedYellow);
		Timer_delay(delay);
		blinks--;
	}
}

float App_delay(float period, uint8_t frequency)
{
	uint8_t checks = period * frequency;
	float delay = 1000.0/(float)frequency;
	while (checks != 0)
	{
		if(Mode == PED)
		return (float)checks/(float)frequency;
		else
		{
			Timer_delay(delay);
		}
		checks--;
	}
	return 0;
}

float App_blink(float period, uint8_t frequency)
{
	uint8_t blinks = frequency * period;
	float delay = 1000.0/(float)frequency;
	while(blinks !=0 )
	{
		if(Mode == NORMAL)
		{
			LED_toggle(&ledCarYellow);
			Timer_delay(delay);
		}
		else
			return (float)blinks/(float)frequency;
		blinks--;
	}
	return 0;
}
void MODE_NORMAL(void)
{
	while(1)
	{
		CarsState = Green_C;
		LED_on(&ledCarGreen);
		LED_on(&ledPedRed);
		period = App_delay(5,2);
		if (Mode == PED)
		{
			press = MODE_PEDESTERIANS();
			if(press == 0)
				continue;
			else
				period = App_delay(period,2);
		}
		CarsState = Yellow_C;
		App_blink(5,2);
		if (Mode == PED)
		{
			press = MODE_PEDESTERIANS();
			if(press == 0)
				continue;
			else
				period = App_blink(period,2);
		}
		CarsState = Red_C;
		LED_off(&ledCarGreen);
		LED_off(&ledCarYellow);
		LED_on(&ledCarRed);
		period = App_delay(5,2);
		if (Mode == PED)
		{
			press = MODE_PEDESTERIANS();
			if(press == 0)
				continue;
			else
				period = App_delay(period,2);
		}
		CarsState = Yellow_C;
		App_blink(5,2);
		if (Mode == PED)
		{
			press = MODE_PEDESTERIANS();
			if(press == 0)
				continue;
			else
				period = App_blink(period,2);
		}
		LED_off(&ledCarRed);
		LED_off(&ledCarYellow);
	}
	
}
uint8_t MODE_PEDESTERIANS(void)
{
	Timer_delay(500.0);
	Mode = NORMAL;
	if (READ_BIT(PIND,2) == 0)
	{
		switch (CarsState)
		{
			case Red_C:
			LED_off(&ledPedRed);
			LED_on(&ledPedGreen);
			Timer_delay(5000.0);
			transition(2,5);
			LED_off(&ledPedGreen);
			LED_off(&ledCarRed);
			break;
			case Green_C:
			CarsState = Yellow_C;
			case Yellow_C:
			transition(2,5);
			LED_off(&ledCarYellow);
			LED_off(&ledPedYellow);
			LED_off(&ledCarGreen);
			LED_off(&ledPedRed);
			LED_on(&ledCarRed);
			LED_on(&ledPedGreen);
			Timer_delay(5000.0);
			transition(2,5);
			LED_off(&ledPedGreen);
			LED_off(&ledCarRed);
			break;
		}
	return 0;
	}
	else
		return 1;
	
}

void App_init(void){
	
	LED_init(&ledCarRed,prtA, 0, "Red");
	LED_init(&ledCarYellow, prtA, 1, "Yellow");
	LED_init(&ledCarGreen, prtA, 2, "Green");
	
	LED_init(&ledPedRed,prtB, 0, "Red");
	LED_init(&ledPedYellow, prtB, 1, "Yellow");
	LED_init(&ledPedGreen, prtB, 2, "Green");
	
	Button_init(&buttonPEDB, prtD, 2, PDC);
	
	sei();
	
	EXT_INT_SENSE(INT0,RIS);
	INT_ENB(INT0);
}
void App_start(void){
	
		MODE_NORMAL();
}

ISR(EXT_INT_0)
{
	
	Mode = PED;
}