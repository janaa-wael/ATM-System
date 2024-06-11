/*
 * LCD.h
 *
 * Created: 2/8/2024 2:11:09 AM
 *  Author: Jana Wael
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../Lib/STD_TYPES.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_INITIALIZATION_8_BIT_MODE			8


/*************************************** CONTROL PINS MACROS ***************************************/
#define CTRL_PORT					PORTD_ID
#define CTRL_PORT_DIR				0x07
#define LCD_RS_PIN					5
#define LCD_RW_PIN					6
#define LCD_EN_PIN					7
/*************************************** DATA PINS MACROS ******************************************/
#define DATA_PORT					PORTC_ID
#define DATA_PORT_DIR				0xFF
#define LCD_D0_PIN					0
#define LCD_D1_PIN					1
#define LCD_D2_PIN					2
#define LCD_D3_PIN					3
#define LCD_D4_PIN					4
#define LCD_D5_PIN					5
#define LCD_D6_PIN					6
#define LCD_D7_PIN					7
/************************************** LCD COMMANDS MACROS *****************************************/
#define LCD_FUNCTION_SET_CMND				0x38
#define LCD_CLEAR_CMND						0x01
#define LCD_CURSOR_OFF_CMND					0x0C
#define LCD_ENTRY_MODE_SET_CMND				0x06
#define LCD_JUMP_TO_2ND_LINE_CMND		0xC0
/*********************************** LCD FUNCTIONS PROTOTYPES **************************************/
void LCD_voidInit(void);
void LCD_voidSendData(char character);
void LCD_voidSendString(char *str);
void LCD_SendCommand(char Data_Value);
void LCD_voidClearScreen(void);
void LCD_voidSetCursor(u8 row, u8 col);
void LCD_voidSetStringPos(u8 row, u8 col, u8 *str);
void LCD_voidSetDataPos(u8 row, u8 col, u8 character);
void ConvertFloatToStr(u16 temp,char *str);
void Print_Distance_To_LCD(f32 distance);
void LCD_voidDeleteCharacters(u8 row, u8 col, u8 length);
void LCD_voidCursorOff();
#endif /* LCD_H_ */ 
