/*
 * DIO.h
 *
 * Created: 2/2/2024 4:20:04 AM
 *  Author: Jana Wael
 */ 


#ifndef DIO_H_
#define DIO_H_


#include "STD_TYPES.h"


/*******************************************
*				Registers				   *
*******************************************/

//PORT A REGISTERS: 

#define PORTA  *((volatile u8*)0x3B)
#define DDRA   *((volatile u8*)0x3A)
#define PINA   *((volatile u8*)0x39)

//PORT B REGISTERS: 
#define PORTB  *((volatile u8*)0x38)
#define DDRB   *((volatile u8*)0X37)
#define PINB   *((volatile u8*)0X36)

//PORT C REGISTERS:
#define PORTC  *((volatile u8*)0x35)
#define DDRC   *((volatile u8*)0x34)
#define PINC   *((volatile u8*)0x33)

//PORT D REGISTERS
#define PORTD  *((volatile u8*)0x32)
#define DDRD   *((volatile u8*)0x31)
#define PIND   *((volatile u8*)0x30)

/*******************************************
*			   Definitions				   *
*******************************************/

#define NUM_OF_PORTS			4
#define NUM_OF_PINS_PER_PORT	8

#define PORTA_ID				0
#define PORTB_ID				1
#define PORTC_ID				2
#define PORTD_ID				3

#define PIN0_ID					0
#define PIN1_ID					1
#define PIN2_ID					2
#define PIN3_ID					3
#define PIN4_ID					4
#define PIN5_ID					5
#define PIN6_ID					6
#define PIN7_ID					7


 /*******************************************
 *			   Types Declaration		    *
 *******************************************/

#define PIN_LOW			0
#define PIN_HIGH		1

#define PIN_INPUT		0
#define PIN_OUTPUT		1

#define PORT_LOW		0
#define PORT_HIGH		0xFF

#define PORT_INPUT		0
#define PORT_OUTPUT		0xFF

 /*******************************************
 *			   Function Prototypes		    *
 *******************************************/

void DIO_voidSetPortDirection(u8 Copy_u8PORT , u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8PORT , u8 Copy_u8Value);
void DIO_voidSetPinDirection(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 Copy_u8PORT,u8 Copy_u8Pin);
u8 DIO_u8GetPortValue(u8 Copy_u8PORT);

#endif /* DIO_H_ */