/*
 * interrupts.h
 *
 * Created: 10/13/2022 12:24:39 PM
 *  Author: Fat7y
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "../../Util/registers.h"
#include "../../Util/typedefs.h"
#include "../../Util/bitManipulation.h"

#define EXT_INT_0	   __vector_1
#define EXT_INT_1	   __vector_2
#define EXT_INT_2	   __vector_3
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

EN_intError_t EXT_INT_SENSE(EN_INT_t INT, EN_INT_SNS_t SNS);
EN_intError_t INT_ENB(EN_INT_t INT);
EN_intError_t INT_DSB(EN_INT_t INT);


#endif /* INTERRUPTS_H_ */