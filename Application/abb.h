/*
 * abb.h
 *
 * Created: 10/13/2022 12:23:14 PM
 *  Author: Fat7y
 */ 


#ifndef ABB_H_
#define ABB_H_

#include "../ECUAL/LED/LED.h"
#include "../ECUAL/Button/Button.h"

#define ledCarRed LEDs[0]
#define ledCarYellow LEDs[1]
#define ledCarGreen LEDs[2]

#define ledPedRed LEDs[3]
#define ledPedYellow LEDs[4]
#define ledPedGreen LEDs[5]

#define buttonPEDB Button[0]

typedef enum EN_moode_t
{
	NORMAL, PED // normal mode and pedestrian mode
}EN_moode_t;

typedef enum EN_carsState_t
{
	Red_C, Yellow_C, Green_C
}EN_carsState_t;

typedef enum EN_priority_t
{
	P_CARS, P_PEDs
}EN_priority_t;

void transition(uint8_t frequency, uint8_t period);
float App_delay(float period, uint8_t frequency);
float App_blink(float period, uint8_t frequency);
void MODE_NORMAL(void);
uint8_t MODE_PEDESTERIANS(void);
void App_init(void);
void App_start(void);

EN_moode_t Mode = NORMAL;
EN_carsState_t CarsState = Green_C;
uint8_t period = 0;
uint8_t press = 0;
ST_LED_t LEDs[6] = {0};
ST_Button_t Button[1] = {0};
EN_buttonState_t buttonState = 0;
ST_LED_t* blinkingLEDs[2] = {&ledCarYellow, &ledPedYellow};


#endif /* ABB_H_ */