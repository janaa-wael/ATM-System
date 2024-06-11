/*
 * APP.c
 *
 * Created: 6/10/2024 10:04:56 PM
 *  Author: Jana Wael
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
#include "../HAL/BUZZER/BUZZER.h"
#include "../HAL/LED/LED.h"
/********************************* APP **********************************/
#include "APP.h"
/************************************************************************/
u8 pass[4] = "123";
u32 balance;

void HAL_Init()
{
	 LCD_voidInit();
	 KEYPAD_voidInit();
	 LEDS_INIT();
}

void APP_voidWelcomeMessage()
{
	 LCD_voidSendString("Hello :)");
	  _delay_ms(2000);
	  LCD_voidClearScreen();
	  LCD_voidSendString("  Welcome to VS");
	  LCD_voidSetCursor(1,0);
	  LCD_voidSendString("    System");
	  _delay_ms(2000);
}

void APP_voidCheckPassword()
{
	u8 login_flag = 0;
	do 
	{
		u8 input_pass[4] = "xxx";
		LCD_voidClearScreen();
		if(!login_flag)
			LCD_voidSendString("Enter password :");
		else
			LCD_voidSendString("Reenter ur pass");
		LCD_voidSetCursor(1,0);
		for(u8 i = 0 ; i < 3 ; i++)
		{
			while(input_pass[i] == 'x')
			input_pass[i] = KEYPAD_READ();
			LCD_voidSendData(input_pass[i]);
		}
		_delay_ms(1000);
		LCD_voidClearScreen();
		if(!strcmp(input_pass,pass))
		{
			login_flag = 0;
			LCD_voidSendString("Correct Password!");
			LED_TOGGLE(GREEN_LED);
		}
		else
		{
			login_flag = 1;
			LCD_voidSendString("Incorrect Pass!!");
			//BUZZER_TOGGLE();
			LED_TOGGLE(RED_LED);
		}
	} while (login_flag == 1);
	
}

u8 APP_u8KeypadInput()
{
	u8 user_choice = 'x';
	while(user_choice == 'x')
		user_choice = KEYPAD_READ();
	return user_choice;
}

void APP_voidPrintMenu()
{
	LCD_voidSetStringPos(0,0,"1- Deposit Money");
	LCD_voidSetStringPos(1,0,"2- Withdraw Money");
	_delay_ms(1500);
	LCD_voidClearScreen();
	LCD_voidSetStringPos(0,0,"3- View Balance");
	LCD_voidSetStringPos(1,0,"4- Change Password");
	_delay_ms(1500);
	LCD_voidClearScreen();
	LCD_voidSendString("Enter ur choice:");
	u8 user_choice = APP_u8KeypadInput();
	LCD_voidSetDataPos(1,0,user_choice);
	_delay_ms(500);
	LCD_voidClearScreen();
	switch(user_choice)
	{
		case '1' :
			APP_voidEnterDepositAmount();
			break;
		case '2' :
			break;
		case '3' :
			APP_voidViewBalance();
			
		
	}
}

void APP_voidEnterDepositAmount()
{
	LCD_voidSendString("Enter deposit amount:");
	u8 deposit_amount[16] = "";
	u8 i = 0;
	LCD_voidSetCursor(1,0);
	do
	{
		deposit_amount[i] = APP_u8KeypadInput();
		if(deposit_amount[i] != '=')
			LCD_voidSendData(deposit_amount[i]);
	}while(deposit_amount[i++] != '=');
	deposit_amount[i-1] = '\0';
	LCD_voidClearScreen();
	LCD_voidSendString("Successfully");
	LCD_voidSetStringPos(1,0,"Deposited :)");
	balance += strtol(deposit_amount,NULL,10);
	
}
void APP_voidConvertIntToStr(u32 x, u8* str)
{
	sprintf(str,"%d",x);
}

void APP_voidViewBalance()
{
	u8 balance_str[16];
	LCD_voidSendString("Balance=");
	APP_voidConvertIntToStr(balance,balance_str);
	LCD_voidSetStringPos(1,0,balance_str);
}