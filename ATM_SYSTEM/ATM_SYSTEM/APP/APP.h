/*
 * APP.h
 *
 * Created: 6/10/2024 10:25:41 PM
 *  Author: Jana Wael
 */ 


#ifndef APP_H_
#define APP_H_

#define PASSWORD_STRENGTH	8


void HAL_Init();
void APP_voidWelcomeMessage();
void APP_voidCheckPassword();
void APP_voidCorrectPassword();
void APP_voidIncorrectPassword();
void APP_voidBuzzerLedIndicator(u8 BUZZER_ID, u8 LED_ID, u8 delay);
void APP_voidPrintMenu();
u8 APP_u8KeypadInput();
void APP_voidEnterDepositAmount();
void APP_voidConvertIntToStr(u32 x, u8* str);
void APP_voidViewBalance();
void APP_voidWithdrawMoney();
u32 APP_voidConvertStrToInt(u8* str);
void APP_voidShoiwWidthdrawWarning();
void APP_voidShowWithdrawMsg();
void APP_voidShowDepositMsg();
void APP_voidInterruptSettingsEnable();
#endif /* APP_H_ */