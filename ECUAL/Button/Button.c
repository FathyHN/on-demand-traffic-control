/*
 * Button.c
 *
 * Created: 10/8/2022 5:05:15 AM
 *  Author: Fat7y
 */ 
#include "Button.h"

EN_buttonError_t Button_init(ST_Button_t* Button, EN_dioPNum_t prtNum, uint8_t pinNum, EN_buttonConfig_t config){
	Button->prtNum = prtNum;
	Button->pinNum = pinNum;
	Button->buttonConfig = config;
	Button->buttonState = notPressed;
	return OK_Button;
}
EN_buttonError_t Button_read(ST_Button_t* Button, EN_buttonState_t* State){
	EN_dioValue_t value = 0;
	DIO_Read(Button->prtNum,Button->pinNum,&value);
	switch (value)
	{
		case LO:
			if (Button->buttonConfig == PDC){
				Button->buttonState = notPressed;
				*State = Button->buttonState;
			}
			else if (Button->buttonConfig == PUC){
				Button->buttonState = pressed;
				*State = Button->buttonState;
			}
			break;
		case HI:
			if (Button->buttonConfig == PDC){
				Button->buttonState = pressed;
				*State = Button->buttonState;
			}
			else if (Button->buttonConfig == PUC){
				Button->buttonState = notPressed;
				*State = Button->buttonState;
			}
			break;
	}
	return OK_Button;
}
