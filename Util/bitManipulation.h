/*
 * bitManipulation.h
 *
 * Created: 10/7/2022 10:53:56 PM
 *  Author: Fat7y
 */ 


#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_

 #define SET_BIT(X,BIT_NO) (X|=(1<<BIT_NO)) // Set bit Macro
 #define CLR_BIT(X,BIT_NO) (X&=~(1<<BIT_NO)) // Clear bit Macro
 #define READ_BIT(X,BIT_NO) ((X & (1<<BIT_NO))>>BIT_NO) // Read bit Macro
 #define TOGGLE_BIT(X,BIT_NO) (X^=(1<<BIT_NO)) //Toggle bit Macro

#endif /* BITMANIPULATION_H_ */