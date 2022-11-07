/*
 * DIO.h
 *
 * Created: 10/7/2022 10:54:52 PM
 *  Author: Fat7y
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Util/registers.h"
#include "../../Util/typedefs.h"
#include "../../Util/bitManipulation.h"

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
EN_dioError_t DIO_init(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioDDR_t direction); //initializing the pin to input or output
EN_dioError_t DIO_Write(EN_dioPNum_t portNum, uint8_t pinNum, EN_dioValue_t value); //Writing high or low values on the pin
EN_dioError_t DIO_Read(EN_dioPNum_t portNum, uint8_t pinNum, uint8_t *value); //read the pin value and put it in the address value
EN_dioError_t DIO_toggle(EN_dioPNum_t portNum, uint8_t pinNum); //toggle the pin value if hight go to low and if low go to high

#endif /* DIO_H_ */