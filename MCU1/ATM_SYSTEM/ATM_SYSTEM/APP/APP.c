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
#include <stdio.h>
#include <stdlib.h>
/********************************* HAL **********************************/
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
/********************************* MCAL *********************************/
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/EXTI/EXTI.h"
#include "../MCAL/ADC/ADC.h"
/********************************* HAL **********************************/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/BUZZER/BUZZER.h"
#include "../HAL/LED/LED.h"
/********************************* APP **********************************/
#include "APP.h"
/************************************************************************/
u8 pass[10] = "123";
u32 balance = 0;

ADC_pfNotification = &APP_voidADC_Callback;

void HAL_Init()
{
	 LCD_voidInit();
	 KEYPAD_voidInit();
	 LEDS_INIT();
	 BUZZER_Init();
	 ADC_voidInit();
	 ADC_voidGetDigitalValueAsynch(ADC_u8_CHANNEL_4,ADC_pfNotification);
}

void APP_voidADC_Callback(u16 ADC_READING)
{
	u8 str_temp[10];
	u8 str_reading[10];
	u32 Temperature = ADC_READING*0.488;
	sprintf(str_temp,"%d",(int)Temperature);
	sprintf(str_reading,"%d",ADC_READING);
	LCD_voidClearScreen();
	LCD_voidSendString("ADC: ");
	LCD_voidSendString(str_reading);
	LCD_voidSetCursor(1, 0);
	LCD_voidSendString("Temp: ");
	LCD_voidSendData(str_temp);
	_delay_ms(4000);
	if(Temperature > 30)
	{
		DIO_voidSetPinDirection(PORTA_ID,PIN7_ID,PIN_OUTPUT);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_HIGH);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_LOW);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_HIGH);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_LOW);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_HIGH);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_LOW);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_HIGH);
		_delay_ms(1000);
		DIO_voidSetPinValue(PORTA_ID,PIN7_ID,PIN_LOW);
	}
}

void APP_voidWelcomeMessage()
{
	 LCD_voidSendString("Hello :)");
	  _delay_ms(2000);
	  LCD_voidClearScreen();
	  LCD_voidSetStringPos(0,1,"Welcome to VS");
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
			APP_voidCorrectPassword();
		}
		else
		{
			login_flag = 1;
			APP_voidIncorrectPassword();
		}
	} while (login_flag == 1);
	
}

void APP_voidCorrectPassword()
{
	LCD_voidSendString("Correct Password!");
	APP_voidBuzzerLedIndicator(BUZZER_PROCEEDING,GREEN_LED,2);
}

void APP_voidIncorrectPassword()
{
	LCD_voidSendString("Incorrect Pass!!");
	APP_voidBuzzerLedIndicator(BUZZER_WARNING,RED_LED,4);
}

void APP_voidBuzzerLedIndicator(u8 BUZZER_ID, u8 LED_ID, u8 delay)
{
	for(u8 i = 0 ; i<8 ; i++)
	{
		LED_TOGGLE(LED_ID);
		BUZZER_TOGGLE(BUZZER_ID);
		for(u8 j = 0 ; j < delay ; j++)
		_delay_ms(100);
	}	
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
			APP_voidWithdrawMoney();
			break;
		case '3' :
			APP_voidViewBalance();
			break;
		case '4' : 	
			APP_voidChangePassword();	
			break;		
	}
}

void APP_voidEnterDepositAmount()
{
	u8 deposit_amount[10] = "";
	u8 i = 0;
	u32 num;
	LCD_voidSendString("Enter deposit amount:");
	LCD_voidSetCursor(1,0);
	do
	{
		deposit_amount[i] = APP_u8KeypadInput();
		if(deposit_amount[i] != '=')
			LCD_voidSendData(deposit_amount[i]);
	}while(deposit_amount[i++] != '=');
	deposit_amount[i-1] = '\0';
	LCD_voidClearScreen();
	num = atoi(deposit_amount);
	balance += num;
	APP_voidShowDepositMsg();
}

void APP_voidWithdrawMoney()
{
	u8 withdrawal_amount[16] = "";
	u8 i = 0;
	u32 num = 0;
	LCD_voidSendString("Enter withdrawal");
	LCD_voidSetStringPos(1,0,"amount:");
	LCD_voidSetCursor(1,7);
	do
	{
		withdrawal_amount[i] = APP_u8KeypadInput();
		if(withdrawal_amount[i] != '=')
			LCD_voidSendData(withdrawal_amount[i]);
	}while(withdrawal_amount[i++] != '=');
	withdrawal_amount[i-1] = '\0';
	LCD_voidClearScreen();
	num = APP_voidConvertStrToInt(withdrawal_amount);
	if(num>balance)
	{
		APP_voidShoiwWidthdrawWarning();
	}
	else
	{
		balance -= num;	
		APP_voidShowWithdrawMsg();
	}
	_delay_ms(1000);

}

void APP_voidViewBalance()
{
	u8 balance_str[16];
	LCD_voidSendString("Balance :");
	APP_voidConvertIntToStr(balance,balance_str);
	LCD_voidSetStringPos(1,0,balance_str);
	_delay_ms(2000);
}

void APP_voidChangePassword()
{
	u8 pass_strength_flag = 1;
	u8 input_pass[10];
	do{
		input_pass[10] = "";
		u8 num_of_characters = 0, i = 0;
		if(pass_strength_flag)
		{
			LCD_voidSetStringPos(2,0,"Change Password :");
			_delay_ms(1000);
		}
		else
		{
			LCD_voidSetStringPos(0,0,"Password len < 8");
			_delay_ms(3000);
			LCD_voidClearScreen();
			LCD_voidSendString("Try again");
		}
		LCD_voidSetCursor(1,0);
		while(input_pass[i-1] != '=')
		{
			input_pass[i] = APP_u8KeypadInput();
			LCD_voidSendData(input_pass[i++]);
			num_of_characters++;
		}
		LCD_voidClearScreen();
		input_pass[i] = '\0';
		pass_strength_flag = ((num_of_characters-1)>=8)? 1:0;
		
	}while(pass_strength_flag == 0);
	strcpy(pass,input_pass);
}

void APP_voidConvertIntToStr(u32 x, u8* str)
{
	sprintf(str, "%d", x);
}


u32 APP_voidConvertStrToInt(u8* str)
{
		int num = 0;
		int sign = 1;
		int i = 0;

		// Handle optional leading whitespaces
		while (str[i] == ' ') {
			i++;
		}

		// Handle optional sign
		if (str[i] == '-') {
			sign = -1;
			i++;
			} else if (str[i] == '+') {
			i++; 
		}

		// Convert digits to integer
		while (str[i] >= '0' && str[i] <= '9') {
			num = num * 10 + (str[i] - '0');
			i++;
		}
		return sign * num;
}

void APP_voidShoiwWidthdrawWarning()
{
	LCD_voidSendString("WARNING!");
	LCD_voidSetStringPos(1,0,"CAN'T WITHDRAW");
	APP_voidBuzzerLedIndicator(BUZZER_WARNING,RED_LED,2);
}

void APP_voidShowWithdrawMsg()
{
		LCD_voidSendString("Successfully");
		LCD_voidSetStringPos(1,0,"Withdrawn :)");
		for(u8 i = 0 ; i <3 ; i++)
		{
			LED_voidToggleDelay(BIBY_LED,200);
		}
}

void APP_voidShowDepositMsg()
{
		LCD_voidSendString("Successfully");
		LCD_voidSetStringPos(1,0,"Deposited :)");
		APP_voidBuzzerLedIndicator(BUZZER_DEPOSITING,BIBY_LED,3);
}

void APP_voidInterruptSettingsEnable()
{
	EXTI_void_GLOABALINT_ENAB();
	EXTI_void_Int0_Init(RISING_EDGE);
	
}