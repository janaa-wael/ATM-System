/*
 * ATM_SYSTEM.c
 *
 * Created: 6/10/2024 8:36:16 PM
 * Author : Jana Wael
 */ 

/************************************************************************/
#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
/********************************* HAL **********************************/
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
/********************************* MCAL *********************************/
#include "../MCAL/DIO/DIO.h"
/********************************* HAL **********************************/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"
/********************************* APP **********************************/
#include "APP.h"
/************************************************************************/

int main(void)
{
	MCAL_init();
	HAL_Init();
	APP_voidWelcomeMessage();
	APP_voidCheckPassword();
	EXTI_voidDisableInterrupt();
	while(1)
	{
			APP_voidPrintMenu();
			EXTI_void_GLOABALINT_ENAB();
			APP_voidADCSendTempUsingUart();
	}
}

