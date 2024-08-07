/*
 * APP.h
 *
 * Created: 6/10/2024 10:25:41 PM
 *  Author: Jana Wael
 */ 


#ifndef APP_H_
#define APP_H_

#define PASSWORD_STRENGTH		8
#define PASSWORD_MAX_TRIALS		3

void HAL_Init();
void MCAL_init();
void APP_voidWelcomeMessage();
void APP_voidCheckPassword();
void APP_voidCorrectPassword();
void APP_voidIncorrectPassword();
void APP_voidLockSystem();
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
void APP_voidPrintTemp();
u64 charArrayToInt(char* str);

#endif /* APP_H_ */