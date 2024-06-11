/*
 * LED.h
 *
 * Created: 6/11/2024 12:20:39 AM
 *  Author: hp
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#define NUM_OF_LEDS		2

#define GREEN_LED		0
#define RED_LED			1

#define LED_LOW			0
#define LED_HIGH		1


void LEDS_INIT();
void LED_ON(u8 LED_ID);
void LED_OFF(u8 LED_ID);
void LED_TOGGLE(u8 LED_ID);

#endif /* LED_H_ */