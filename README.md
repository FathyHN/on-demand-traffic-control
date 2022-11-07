# on-demand-traffic-control
System Description
An on-demand traffic control system consists of 6 leds, the colors in pairs are Red, Yellow and
Green. Also a button is added as the request button. The traffic controlled by 2 traffic lights each
with one led of each pair these traffic lights are supposed to manage the priority between cars
and pedestrians want to cross the road. The system is controlled with an ATmega 32
microcontroller. The Cars traffic light leds are connected to pins 0, 1, and 2 in port A and the
pedestrian traffic light leds are connected to the same pins numbers in port B, which means that
these pins are initialized and configured as output pins and the pedestrians button is connected
to pin 2 in port D which means it’s connected to the external interrupt number 0.
The system will work in 2 modes

-Normal Mode is when no one has pressed on the pedestrians button the red light of
    the pedestrians traffic light is on and the green light of the cars traffic light is on for
    5 seconds. Then the yellow led of the cars traffic light will blink for 5 seconds when
    the Green light is still on then both yellow and green leds will be off and the red
    light will be on. The pedestrians are not allowed to cross the road until someone
    presses the pedestrians button
-Pedestrians mode is activated when the button is pressed. Depending on the Cars
    traffic light state when the button is pressed the pedestrian mode will work in 2
    different scenarios
    o When Cars traffic light is Red the green pedestrian light will be on
    immediately for 5 seconds, then both yellow light will blink for 5 seconds
    then the pedestrians red light is on again and the cars green light is on
    When the cars traffic light is Green or Yellow, both yellow lights will blink for
    5 seconds and the pedestrians green light is on for 5 seconds when the cars
    red is on and then both yellow lights blink for 5 seconds again before the
    pedestrians traffic light back to Red state and the cars traffic light back to
    Green
    
System Design
Layered Architecture
System layers from top to bottom:
-Application
-Electronic Unit Abstraction Layer (ECUAL)
-Microcontroller Abstraction Layer (MCAL)
-Microcontroller

System Drivers
-Electronic Unit Abstraction Layer
    o LED Driver
    o Button Driver
-Microcontroller Abstraction Layer
    o DIO Driver
    o Timers Driver
    o External interrupts driver
    
    DIO Driver
EN_dioError_t DIO_init(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioDDR_t
direction); //initializing the pin to input or output
- This Function will initialize the pin as INPUT or OUTPUT using Port
number and Pin number and the type in the 3rd argument
- This function will return OK_DIO if the port number, pin Number, and the
direction are specified correctly, else, it will return an error for
each wrong case separately

EN_dioError_t DIO_Write(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioValue_t
value); //Writing high or low values on the pin
- This function will write high or low values to the previously
initialized pin as output using the pin number and port number and the
value wanted in the arguments

EN_dioError_t DIO_Read(EN_dioPNum_t portNum, uint8_t pinNum, uint8_t *value);
//read the pin value and put it in the address value
-This function will read the value of the pin specified from the
arguments and return it to the location where the pointer at the 3rd
argument refer to


EN_dioError_t DIO_toggle(EN_dioPNum_t portNum, uint8_t pinNum); //toggle the pin
value if hight go to low and if low go to high
 -This function will toggle the value of the pin specified from high to
low or vice versa
-------------------------------------------------------------------------------------
typedef enum EN_dioError_t
{
OK_DIO, WRONG_DDR, WRONG_VAL, PORTOVR
}EN_dioError_t;
typedef enum EN_dioDDR_t
{
IN, OUT
} EN_dioDDR_t;
typedef enum EN_dioPNum_t
{
prtA, prtB, prtC, prtD
}EN_dioPNum_t;
typedef enum EN_dioValue_t
{
LO, HI
}EN_dioValue_t;
---------------------------------------------------------
Timers Driver
EN_timerError_t Timer_init(EN_timerNO_t timerNo, EN_timerMode_t opMode, EN_inter_t
interRe, uint16_t initValue);
 -This function will initialize the timer specified in the 1 st argument
with the operation mode specified in the 2nd argument and whether its
interrupt request flag is up or not and the initial value of the timer.

EN_timerError_t Timer_Start(EN_timerNO_t timerNo, EN_clockPrescaler_t prescaler);
 -This function will start the timer specified in the 1st argument using
the prescaler value in the 2nd argument.

EN_timerError_t Timer_Stop(EN_timerNO_t timerNo);
-This function will stop the timer specified in its argument by clearing
clock mode bits.
EN_timerError_t Timer_Read(EN_timerNO_t timerNo, uint16_t* value);
-This function will return the timer value to the location where the
pointer in the second argument is referring to.
EN_timerError_t Timer_delay(float delay);
-This function will perform a delay and will use the suitable technique according to
the requested delay period in comparison to the clock speed (tick time) and will
decide whether to use prescaling to reduce the number of overflows ( if delay >>
tick ) or not.
---------------------------------------------------------------------------------------------
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
----------------------------------------------------------------------------------------
Interrupts Driver
EN_intError_t EXT_INT_SENSE(EN_INT_t INT, EN_INT_SNS_t SNS);
- This function will initialize the external interrupt by using the
interrupt number in 1st argument (INT0, INT1, or INT2) and set its sense
to low level, logical change, falling edge or rising edge.

EN_intError_t INT_ENB(EN_INT_t INT);
 -This function will enable the interrupt after setting its sense with
EXT_INT_SNSE

EN_intError_t INT_DSB(EN_INT_t INT);
- This function will disable the interrupt specified in its argument
-------------------------------------------------------------------------------------------
#define EXT_INT_0
 __vector_1
#define EXT_INT_1
 __vector_2
#define EXT_INT_2
 __vector_3
#define sei() SET_BIT(SREG,7);
#define cli() CLR_BIT(SREG,7);
#define ISR(INT_vect) void INT_vect(void)__attribute__((signal,used));\
void INT_vect(void)

typedef enum EN_INT_t
{
INT0, INT1, INT2
}EN_INT_t;
typedef enum EN_INT_SNS_t
{
LW, LOG_CHNG, RIS, FAL
}EN_INT_SNS_t;
typedef enum EN_intError_t
{
INT_OK, WRONG_INT, WRONG_EXT_INT_MODE
}EN_intError_t;
----------------------------------------------------------------------------
LED Driver
EN_ledError_t LED_init(ST_LED_t* LED, EN_dioPNum_t prtNum, uint8_t pinNum, char
color[]);
- This function will initialize a new led and will store its specification
(color, port and pin number it’s connected to, state initialized as off)
in the Led data structure being pointer at by the pointer in the 1st
argument.
EN_ledError_t LED_on(ST_LED_t* LED);
-This function will deliver high value to the pin the led specified in
the argument is connected to and will change its state to on.

EN_ledError_t LED_off(ST_LED_t* LED);
-This function will deliver low value to the pin the led specified in the
argument is connected to and will change its state to off.

EN_ledError_t LED_toggle(ST_LED_t* LED);
-This function will toggle the value off the pin the led specified in the
argument is connected to and will toggle its state in the data
structure.
---------------------------------------------------------------------------------------
typedef enum EN_ledError_t
{
LED_OK, LED_notFound
}EN_ledError_t;
typedef enum EN_ledState_t
{
off, on
}EN_ledState_t;
typedef struct ST_LED_t
{
uint8_t color[7];
EN_ledState_t state;
EN_dioPNum_t prtNum;
uint8_t pinNum;
}ST_LED_t;
----------------------------------------------------------------------
Button Driver
EN_buttonError_t Button_init(ST_Button_t* Button, EN_dioPNum_t prtNum, uint8_t
pinNum, EN_buttonConfig_t config);
- This function will initialize the button by setting the pin it’s
connected to as INPUT and will initialize its state as not pressed in
the data structure being pointed to by the button in the first argument,
also it will specify whether it’s connected in the Pull down interface
or pull up interface.

EN_buttonError_t Button_read(ST_Button_t* Button, EN_buttonState_t* State);
-This function will read the button state and return the value to the location where
the pointer in the 2nd argument is referring.
-----------------------------------------------------------------------------------------------------
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
typedef struct Button
{
EN_dioPNum_t prtNum;
uint8_t pinNum;
EN_buttonConfig_t buttonConfig;
EN_buttonState_t buttonState;
}ST_Button_t;
