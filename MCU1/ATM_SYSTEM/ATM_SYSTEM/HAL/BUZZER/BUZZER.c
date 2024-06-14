/*
 * BUZZER.c
 *
 * Created: 6/10/2024 11:54:23 PM
 *  Author: Jana Wael
 */ 
#include <avr/delay.h>
/********************************** LIB ***********************************/
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
/********************************* MCAL ***********************************/
#include "../../MCAL/DIO/DIO.h"

#include "BUZZER.h"

u8 BUZZERS[NUM_OF_BUZZERS] = {BUZZER_WARNING,BUZZER_PROCEEDING,BUZZER_DEPOSITING};
u8 BUZZERS_PORT[NUM_OF_BUZZERS] = {PORTA_ID,PORTA_ID,PORTB_ID};
u8 BUZZERS_PIN[NUM_OF_BUZZERS] = {PIN5_ID,PIN6_ID,PIN4_ID};

void BUZZER_Init()
{
	for(u8 i = 0 ; i < NUM_OF_BUZZERS ; i++)
	{
		DIO_voidSetPinDirection(BUZZERS_PORT[i],BUZZERS_PIN[i],PIN_OUTPUT);
		BUZZER_OFF(i);
	}
}

void BUZZER_ON(u8 BUZZER_ID)
{
	DIO_voidSetPinValue(BUZZERS_PORT[BUZZER_ID],BUZZERS_PIN[BUZZER_ID],PIN_HIGH);
}

void BUZZER_OFF(u8 BUZZER_ID)
{
	DIO_voidSetPinValue(BUZZERS_PORT[BUZZER_ID],BUZZERS_PIN[BUZZER_ID],PIN_LOW);
}

void BUZZER_TOGGLE(u8 BUZZER_ID)
{
	if(BUZZER_ID == BUZZER_DEPOSITING)
		TOGGLE_BIT(PORTB,BUZZERS_PIN[BUZZER_ID]);
	else
		TOGGLE_BIT(PORTA,BUZZERS_PIN[BUZZER_ID]);
}
