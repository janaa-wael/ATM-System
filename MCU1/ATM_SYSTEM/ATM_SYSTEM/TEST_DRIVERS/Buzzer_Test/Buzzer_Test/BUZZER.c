/*
 * BUZZER.c
 *
 * Created: 6/10/2024 11:54:23 PM
 *  Author: hp
 */ 
#include <avr/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO.h"

#include "BUZZER.h"

void BUZZER_Init()
{
	DIO_voidSetPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	BUZZER_OFF();
}

void BUZZER_ON()
{
	DIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN,PIN_HIGH);
}

void BUZZER_OFF()
{
	DIO_voidSetPinValue(BUZZER_PORT,BUZZER_PIN,PIN_LOW);
}

void BUZZER_TOGGLE()
{
	BUZZER_ON();
	_delay_ms(4000);
	BUZZER_OFF();
}