/*
 * Button.h
 *
 * Created: 10/8/2022 5:05:32 AM
 *  Author: Fat7y
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/Timer.h"
#include "../../MCAL/interrupts/interrupts.h"

typedef enum EN_buttonError_t
{
	OK_Button, Button_NOT_Found
}EN_buttonError_t;

typedef enum EN_buttonState_t
{
	notPressed, pressed
}EN_buttonState_t;

typedef enum EN_buttonConfig_t
{
	PDC, PUC // PDC == Pull Down Configuration, PUC == Pull Up configuration
}EN_buttonConfig_t;

typedef struct Button{
	EN_dioPNum_t prtNum;
	uint8_t pinNum;
	EN_buttonConfig_t buttonConfig;
	EN_buttonState_t buttonState;
	}ST_Button_t;
	
	EN_buttonError_t Button_init(ST_Button_t* Button, EN_dioPNum_t prtNum, uint8_t pinNum, EN_buttonConfig_t config);
	EN_buttonError_t Button_read(ST_Button_t* Button, EN_buttonState_t* State);
#endif /* BUTTON_H_ */