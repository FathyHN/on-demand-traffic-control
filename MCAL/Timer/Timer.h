/*
 * Timer.h
 *
 * Created: 10/10/2022 11:08:17 PM
 *  Author: Fat7y
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Util/registers.h"
#include "../../Util/typedefs.h"
#include "../../Util/bitManipulation.h"

typedef enum EN_timerError_t
{
	timer_OK, Wrong_Mode, Wrong_TimerNO, Wrong_interMode, Wrong_prescaler
}EN_timerError_t;


typedef enum EN_timerMode_t
{
	Normal, CTC, fastPWM, crPhasePWM
}EN_timerMode_t;

typedef enum EN_timerNO_t
{
	Timer0, Timer1, Timer2
}EN_timerNO_t;

typedef enum EN_inter_t
{
	none, OCM_inter, OVF_inter, timerBothInter
}EN_inter_t;

typedef enum EN_clockPrescaler_t
{
	_1, _8, _64, _256, _1024, exFall, exRise
}EN_clockPrescaler_t;


EN_timerError_t Timer_init(EN_timerNO_t timerNo, EN_timerMode_t opMode, EN_inter_t interRe, uint16_t initValue);
EN_timerError_t Timer_Start(EN_timerNO_t timerNo, EN_clockPrescaler_t prescaler);
EN_timerError_t Timer_Stop(EN_timerNO_t timerNo);
EN_timerError_t Timer_Read(EN_timerNO_t timerNo, uint16_t* value);
EN_timerError_t Timer_delay(float delay);



#endif /* TIMER_H_ */