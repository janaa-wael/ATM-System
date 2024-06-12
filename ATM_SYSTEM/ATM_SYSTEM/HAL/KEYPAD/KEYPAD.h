/*
 * KEYPAD.h
 *
 * Created: 6/9/2024 7:44:57 PM
 *  Author: Jana Wael
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"

/* NUMBER OF ROWS AND COLUMNS */
#define KEYPAD_ROW_PORT				PORTA_ID
#define KEYPAD_COL_PORT				PORTB_ID

#define COL_PORT_OUTPUT				0x0F
#define ROW_PORT_INPUT				0x00

/* PORT CONFIGURATIONS */
#define KEYPAD_R0_PIN			0
#define KEYPAD_R1_PIN			1
#define KEYPAD_R2_PIN			2
#define KEYPAD_R3_PIN			3

#define KEYPAD_C0_PIN			0
#define KEYPAD_C1_PIN			1
#define KEYPAD_C2_PIN			2
#define KEYPAD_C3_PIN			3

#define	COL_INIT				0
#define COL_FINAL				3
#define ROW_INIT				0
#define ROW_FINAL				3

#define KEYPAD_NUM_ROWS 		4
#define KEYPAD_NUM_COLS			4

#define KEYPAD_BUTTON_PRESSED		PIN_LOW
#define KEYPAD_BUTTON_RELEASED		PIN_HIGH

#define KPD_VALUES     {{'7','8','9','÷'},\
{'4','5','6','*'},\
{'1','2','3','-'},\
{'c','0','=','+'}}

void KEYPAD_voidInit(void);
u8 KEYPAD_READ(void);


#endif /* KEYPAD_H_ */