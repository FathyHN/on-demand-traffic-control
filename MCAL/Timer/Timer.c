/*
 * Timer.c
 *
 * Created: 10/10/2022 11:08:03 PM
 *  Author: Fat7y
 */ 
#include "Timer.h"
#include <math.h>
EN_timerError_t Timer_init(EN_timerNO_t timerNo, EN_timerMode_t opMode, EN_inter_t interRe, uint16_t initValue){
	switch(timerNo){
		case Timer0:
			if(opMode == Normal)
				TCCR0 = 0x00;
			else if(opMode == crPhasePWM)
			{
				TCCR0 = 0x00;
				SET_BIT(TCCR0,6);
			}
			else if (opMode == CTC)
			{
				TCCR0 = 0x00;
				SET_BIT(TCCR0,3);
			}
			else if (opMode == fastPWM)
			{
				TCCR0 = 0x00;
				SET_BIT(TCCR0,3);
				SET_BIT(TCCR0,6);
			}
			else
				return Wrong_interMode;
			
			if(interRe == none)
			{
				CLR_BIT(TIMSK,0);
				CLR_BIT(TIMSK,1);
			}
			else if(interRe == OCM_inter)
			{
				CLR_BIT(TIMSK,0);
				SET_BIT(TIMSK,1);
			}
			else if(interRe == OVF_inter)
			{
				SET_BIT(TIMSK,0);
				CLR_BIT(TIMSK,1);
			}
			else if (interRe == timerBothInter)
			{
				SET_BIT(TIMSK,0);
				SET_BIT(TIMSK,1);
			}
			else
				return Wrong_interMode;
			
			TCNT0 = initValue;
			
			break;
		case Timer1:
			break;
		case Timer2:
			break;
	}
	return timer_OK;
}
EN_timerError_t Timer_Start(EN_timerNO_t timerNo, EN_clockPrescaler_t prescaler){
		switch(timerNo){
			case Timer0:
				if(prescaler == _1)
				{
					SET_BIT(TCCR0,0);
					CLR_BIT(TCCR0,1);
					CLR_BIT(TCCR0,2);
				}
				else if (prescaler == _8)
				{
					CLR_BIT(TCCR0,0);
					SET_BIT(TCCR0,1);
					CLR_BIT(TCCR0,2);
				}
				else if (prescaler == _64)
				{
					SET_BIT(TCCR0,0);
					SET_BIT(TCCR0,1);
					CLR_BIT(TCCR0,2);
				}
				else if (prescaler == _256)
				{
					CLR_BIT(TCCR0,0);
					CLR_BIT(TCCR0,1);
					SET_BIT(TCCR0,2);
				}
				else if (prescaler == _1024)
				{
					SET_BIT(TCCR0,0);
					CLR_BIT(TCCR0,1);
					SET_BIT(TCCR0,2);
				}
				else if(prescaler == exFall)
				{
					CLR_BIT(TCCR0,0);
					SET_BIT(TCCR0,1);
					SET_BIT(TCCR0,2);
				}
				else if(prescaler == exRise)
				{
					SET_BIT(TCCR0,0);
					SET_BIT(TCCR0,1);
					SET_BIT(TCCR0,2);
				}
				else
					return Wrong_prescaler;
			break;
			case Timer1:
			break;
			case Timer2:
			break;
		}
	return timer_OK;
}
EN_timerError_t Timer_Stop(EN_timerNO_t timerNo){
	switch(timerNo){
		case Timer0:
			CLR_BIT(TCCR0,0);
			CLR_BIT(TCCR0,1);
			CLR_BIT(TCCR0,2);
		break;
		case Timer1:
		break;
		case Timer2:
		break;
	}
	return timer_OK;
}
EN_timerError_t Timer_Read(EN_timerNO_t timerNo, uint16_t* value){
	switch(timerNo){
		case Timer0:
			*value = TCNT0;
		break;
		case Timer1:
		break;
		case Timer2:
		break;
	}
	return timer_OK;
}

EN_timerError_t Timer_delay(float delay)
{
	float tick = 1/1000000.0;
	float maxDelay = tick * pow(2.0,8.0);
	delay /= 1000.0;
	if(delay < maxDelay)
	{
		uint8_t init = (maxDelay - delay) / tick;	
		Timer_init(Timer0,Normal,none,init);
		Timer_Start(Timer0,_1);
		while(!(READ_BIT(TIFR,0)));
		SET_BIT(TIFR,1);
	}
	else if (delay == maxDelay)
	{
		Timer_init(Timer0,Normal,none,0);
		Timer_Start(Timer0,_1);
		while(!(READ_BIT(TIFR,0)));
		SET_BIT(TIFR,1);
	}
	else
	{
		tick *= 1024;
		maxDelay *= 1024.0;
		if(delay < maxDelay)
		{
			uint8_t init = (maxDelay - delay) / tick;
			Timer_init(Timer0,Normal,none,init);
			Timer_Start(Timer0,_1);
			while(!(READ_BIT(TIFR,0)));
			SET_BIT(TIFR,1);
		}
		else if (delay == maxDelay)
		{
			Timer_init(Timer0,Normal,none,0);
			Timer_Start(Timer0,_1);
			while(!(READ_BIT(TIFR,0)));
			SET_BIT(TIFR,1);
		}
		else
		{
			uint8_t ovrflow = ceil(delay/maxDelay);
			uint8_t init = pow(2.0,8.0) - delay/tick/ovrflow;
			Timer_init(Timer0,Normal,none,init);
			Timer_Start(Timer0,_1024);
			
			while(ovrflow != 0)
			{
				while(!(READ_BIT(TIFR,0)));
				SET_BIT(TIFR,1);
				ovrflow--;
			}
		}
	}
	
	Timer_Stop(Timer0);
	return timer_OK;
}