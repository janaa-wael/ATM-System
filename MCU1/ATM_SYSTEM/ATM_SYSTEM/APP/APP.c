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
/********************************* Lib **********************************/
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
/********************************* MCAL *********************************/
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/EXTI/EXTI.h"
#include "../MCAL/ADC/ADC.h"
#include "../MCAL/UART/UART.h"
/********************************* HAL **********************************/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/BUZZER/BUZZER.h"
#include "../HAL/LED/LED.h"
/********************************* APP **********************************/
#include "APP.h"
#include "User.h"
/************************************************************************/
u8 pass[10] = "123";
u64 balance = 0;

void HAL_Init()
{
	 LCD_voidInit();
	 KEYPAD_voidInit();
	 LEDS_INIT();
	 BUZZER_Init();
}

void MCAL_init()
{
	UART_init(9600);
	ADC_Init();
}

void APP_voidSignInOrLogIn()
{
	char input_choice;
	LCD_voidSendString("1- Sign In");
	LCD_voidSetStringPos(1,0,"2- Log In");
	
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
	u8 num_of_pass_trials = 0;
	do 
	{
		u8 input_pass[16] = "";
		u8 kpd_input = 0 , i = 0;
		LCD_voidClearScreen();
		if(!login_flag)
			LCD_voidSendString("Enter password :");
		else
			LCD_voidSendString("Reenter ur pass");
		LCD_voidSetCursor(1,0);
		do
		{
			input_pass[i] = APP_u8KeypadInput();
			LCD_voidSendData(input_pass[i]);
		}while(input_pass[i++] != '=');
		LCD_voidClearScreen();
		input_pass[i-1] = '\0';
		if(!strcmp(input_pass,pass))
		{
			login_flag = 0;
			APP_voidCorrectPassword();
		}
		else
		{
			login_flag = 1;
			APP_voidIncorrectPassword();
			num_of_pass_trials++;
		}
	} while (login_flag == 1 && num_of_pass_trials<3);
	if(num_of_pass_trials>2)
	{
		APP_voidLockSystem();
	}
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
	u8 num_of_blinks = 0 ;
	if(LED_ID == RED_LED)
		num_of_blinks = 8;
	else 
		num_of_blinks = 4;
	for(u8 i = 0 ; i<num_of_blinks ; i++)
	{
		LED_TOGGLE(LED_ID);
		BUZZER_TOGGLE(BUZZER_ID);
		for(u8 j = 0 ; j < delay ; j++)
		_delay_ms(100);
	}	
}

void APP_voidLockSystem()
{
	char count_down[3];
	LCD_voidClearScreen();
	LCD_voidSendString("You exceeded max");
	LCD_voidSetStringPos(1,0,"number of trials!");
	_delay_ms(3000);
	LCD_voidClearScreen();
	LCD_voidSendString("System is locked");
	LCD_voidSetStringPos(1,0,"Try again in");
	for(int i = 30 ; i>=0 ; i--)
	{
		sprintf(count_down,"%d",i);
		_delay_ms(1000);
		LCD_voidSetStringPos(1,13,count_down);
		LCD_voidSendData('s');
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
	APP_voidADCSendTempUsingUart();
}

void APP_voidEnterDepositAmount()
{
	u8 deposit_amount[10] = "";
	u8 i = 0, invalid_input_flag = 0;
	s64 num;

	do 
	{
		LCD_voidClearScreen();
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
		num = APP_voidConvertStrToInt(deposit_amount);
		if(num>0)
		{
			balance += num;
			UART_sendByte('d');
			APP_voidShowDepositMsg();
			invalid_input_flag = 0;
		}
		else
		{
			LCD_voidClearScreen();
			LCD_voidSendString("Invalid Input");
			LCD_voidSetStringPos(1,0,"Please try again");
			_delay_ms(2000);
			invalid_input_flag = 1;
		}
	} while (invalid_input_flag == 1);

}

void APP_voidWithdrawMoney()
{
	u8 withdrawal_amount[16] = "";
	u8 i = 0;
	s32 num = 0;
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
	if(num>balance || num<0)
	{
		APP_voidShoiwWidthdrawWarning();
	}
	else
	{
		UART_sendByte('w');
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

void APP_voidADCSendTempUsingUart()
{
	f32 temp_celsius;
	temp_celsius = (ADC_Read()*0.488);
	if((int)temp_celsius>30)
	{
		UART_sendByte('y');
	}
	else
	{
		UART_sendByte('n');
	}
}

void APP_voidPrintTemp()
{
	float celsius;
	u8 Temperature[5];
	/* Replace with your application code */
	while (1)
	{
		LCD_voidClearScreen();
		_delay_ms(1000);
		celsius = (ADC_Read()*0.488);
		sprintf(Temperature,"%d%cC", (int)celsius, 0xdf);/* convert integer value to ASCII string */
		LCD_voidSendString(Temperature);
		_delay_ms(3000);
	}
}

u64 charArrayToInt(char* str) {
	u64 num = 0;
	int i = 0;
	
	// Iterate through each character of the array
	while (str[i] != '\0') {
		// Convert character to integer and add to num
		num = num * 10 + (str[i] - '0');
		i++;
	}
	
	return num;
}