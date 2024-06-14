/*
 * Timer.c
 *
 * Created: 6/14/2024 3:35:41 AM
 *  Author: Jana Wael
 */ 
#include <avr/io.h>
#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

void PWM_voidInit() {
	// Set Fast PWM mode, non-inverting
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // Fast PWM, Prescaler=8
	  TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS22); // Fast PWM, non-inverting mode, Prescaler=64
	
}

void PWM_voidSetDutyCycle_OC0(u8 duty_cycle) {
	OCR0 = duty_cycle;
}

void PWM_voidSetDutyCycle_OC2(u16 duty_cycle) {
    OCR2 = duty_cycle; // Directly set the duty cycle
}