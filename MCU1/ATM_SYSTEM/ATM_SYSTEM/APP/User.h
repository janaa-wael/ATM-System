/*
 * User.h
 *
 * Created: 7/1/2024 12:04:35 PM
 *  Author: Jana Wael
 */ 


#ifndef USER_H_
#define USER_H_

/********************************* HAL **********************************/
#include "../HAL/KEYPAD/KEYPAD.h"
#include "../HAL/LCD/LCD.h"
/********************************* Lib **********************************/
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
/********************************* APP **********************************/
#include "APP.h"

void User_voidAddUser();
u8 User_voidSignIn(u8 id[], u8 password[]);

#endif /* USER_H_ */