/*
 * interrupts.c
 *
 * Created: 10/13/2022 1:57:15 PM
 *  Author: Fat7y
 */ 
#include "interrupts.h"



EN_intError_t EXT_INT_SENSE(EN_INT_t INT, EN_INT_SNS_t SNS)
{
	switch (INT)
	{
		case INT0:
			if(SNS == LW)
				{
					CLR_BIT(MCUCR,0);
					CLR_BIT(MCUCR,1);
				}
			else if(SNS == LOG_CHNG)
				{
					SET_BIT(MCUCR,0);
					CLR_BIT(MCUCR,1);
				}
			else if(SNS == FAL)
				{
					CLR_BIT(MCUCR,0);
					SET_BIT(MCUCR,1);
				}
			else if(SNS == RIS)
				{
					SET_BIT(MCUCR,0);
					SET_BIT(MCUCR,1);
				}
			else
				return WRONG_EXT_INT_MODE;
			break;
		
		case INT1:
			if(SNS == LW)
			{
				CLR_BIT(MCUCR,2);
				CLR_BIT(MCUCR,3);
			}
			else if(SNS == LOG_CHNG)
			{
				SET_BIT(MCUCR,2);
				CLR_BIT(MCUCR,3);
			}
			else if(SNS == FAL)
			{
				CLR_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
			}
			else if(SNS == RIS)
			{
				SET_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
			}
			else
			return WRONG_EXT_INT_MODE;
			break;
		
		case INT2:
			if(SNS == FAL)
				CLR_BIT(MCUCSR,6);
			else if(SNS == RIS)
				SET_BIT(MCUCSR,6);
			else
				return WRONG_EXT_INT_MODE;
			break;
			
		default:
			return WRONG_INT;
		break;
	}
	
	return INT_OK;
}
EN_intError_t INT_ENB(EN_INT_t INT)
{
	switch (INT)
	{
		case INT0:
			SET_BIT(GICR,6);
			break;
		case INT1:
			SET_BIT(GICR,7);
			break;
		case INT2:
			SET_BIT(GICR,5);
			break;
		default:
			return WRONG_INT;
			break;
	}
	return INT_OK;
}
EN_intError_t INT_DSB(EN_INT_t INT)
{
	switch (INT)
	{
		case INT0:
			if(READ_BIT(GIFR,6))
				SET_BIT(GIFR,6);
			CLR_BIT(GICR,6);
			break;
		case INT1:
			if(READ_BIT(GIFR,7))
				SET_BIT(GIFR,7);
			CLR_BIT(GICR,7);
			break;
		case INT2:
			if(READ_BIT(GIFR,5))
				SET_BIT(GIFR,5);
			CLR_BIT(GICR,5);
			break;
		default:
			return WRONG_INT;
			break;
	}
	return INT_OK;
}