/*
 * User.c
 *
 * Created: 7/1/2024 12:04:23 PM
 *  Author: Jana Wael
 */ 

/********************************* HAL **********************************/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"
/********************************* Lib **********************************/
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
/********************************* APP **********************************/
#include "APP.h"

struct User{
	u8 id[6];
	u8 password[6];	
};

u8 number_of_users;
struct User arr[10];

void User_voidAddUser()
{
	u8 KEYPAD_INPUT;
	LCD_voidClearScreen();
	LCD_voidSendString("Create ID of 3 char:");
	for(u8 i = 0 ; i < 6 ; i++)
	{
		arr[number_of_users].id[i] = APP_u8KeypadInput();
	}
	LCD_voidClearScreen();
	LCD_voidSendString("Create password of 6 char:");
	for(u8 i = 0 ; i < 6 ; i++)
	{
		arr[number_of_users].password[i] = APP_u8KeypadInput();
	}
	number_of_users++;
}

u8 User_voidSignIn(u8 id[], u8 password[])
{
	u8 i ;
	u8 user_found_flag = 0;
	for(i = 0 ; i < number_of_users ; i++)
	{
		if(strcmp(id,arr[i].id) == 0)
		{
			user_found_flag = 1;
			break;
		}
	}
	if(user_found_flag)
	{
		if(strcmp(password,arr[i].password)==0)
		{
			return 1;
		}
	}
	return 0;

}