/*
 * LED.c
 *
 * Created: 6/11/2024 12:20:28 AM
 *  Author: Jana Wael
 */ 

#include <avr/delay.h>
#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "LED.h"

u8 LEDS[NUM_OF_LEDS] = {GREEN_LED,RED_LED,BIBY_LED};
u8 LEDS_PORT[NUM_OF_LEDS] = {PORTB_ID,PORTB_ID,PORTB_ID};
u8 LEDS_PIN[NUM_OF_LEDS] = {PIN5_ID,PIN6_ID,PIN7_ID};

void LEDS_INIT()
{
	for(u8 i = 0 ; i < NUM_OF_LEDS ; i++)
	{
		DIO_voidSetPinDirection(LEDS_PORT[i],LEDS_PIN[i],PIN_OUTPUT);
		DIO_voidSetPinValue(LEDS_PORT[i],LEDS_PIN[i],LED_LOW);
	}
}

void LED_ON(u8 LED_ID)
{
	DIO_voidSetPinValue(LEDS_PORT[LED_ID],LEDS_PIN[LED_ID],LED_HIGH);
}

void LED_OFF(u8 LED_ID)
{
	DIO_voidSetPinValue(LEDS_PORT[LED_ID],LEDS_PIN[LED_ID],LED_LOW);
}

void LED_TOGGLE(u8 LED_ID)
{
	TOGGLE_BIT(PORTB,LEDS_PIN[LED_ID]);
}

void LED_voidToggleDelay(u8 LED_ID, u32 delay)
{
	u8 i;
	LED_ON(LED_ID);
	for(i  = 0 ; i < delay ; i++)
		_delay_ms(1);
	LED_OFF(LED_ID);
	for(i  = 0 ; i < delay ; i++)
	_delay_ms(1);
	
}