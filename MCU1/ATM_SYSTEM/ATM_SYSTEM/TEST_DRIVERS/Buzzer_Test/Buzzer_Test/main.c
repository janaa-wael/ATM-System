/*
 * Buzzer_Test.c
 *
 * Created: 6/12/2024 5:54:07 PM
 * Author : Jana Wael
 */ 

#include <avr/io.h>
#include "DIO.h"
#include "BUZZER.h"
#include "STD_TYPES.h"
#include "BUZZER.h"

int main(void)
{
	DIO_voidSetPortDirection(PORTB_ID,PORT_OUTPUT);
	BUZZER_OFF();
    /* Replace with your application code */
    while (1) 
    {
		BUZZER_TOGGLE();
    }
}

