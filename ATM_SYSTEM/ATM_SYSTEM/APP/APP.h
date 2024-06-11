/*
 * APP.h
 *
 * Created: 6/10/2024 10:25:41 PM
 *  Author: hp
 */ 


#ifndef APP_H_
#define APP_H_

void HAL_Init();
void APP_voidWelcomeMessage();
void APP_voidCheckPassword();
void APP_voidPrintMenu();
u8 APP_u8KeypadInput();
void APP_voidEnterDepositAmount();
void APP_voidConvertIntToStr(u32 x, u8* str);
void APP_voidViewBalance();

#endif /* APP_H_ */