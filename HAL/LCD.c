/*
 * LCD.c
 *
 * Created: 2/8/2024 2:10:53 AM
 *  Author: Jana Wael
 */ 


#include <avr/delay.h>
#include "../Lib/BIT_MATH.h"
#include "../Lib/STD_TYPES.h"
#include "../MCAL/DIO.h"
#include "LCD.h"



/* 
 * Description : 
 * Control Port Direction : OUTPUT
 * Data Port Direction : OUTPUT
 * Delay of 1 second 
 * Initializing 8-bit mode
 * Delay of 1 second
 * Clear Command
 * Delay of 1 second
 * Turning cursor of LCD off
 * Delay of 1 second
 * Sending Entry mode set command
 */
void LCD_voidInit()
{
	_delay_us(300);
	LCD_SendCommand(LCD_FUNCTION_SET_CMND);
	_delay_ms(1);
	LCD_SendCommand(0x0F);
	_delay_ms(2);
	LCD_SendCommand(0x01);
	_delay_ms(5);
	LCD_SendCommand(LCD_ENTRY_MODE_SET_CMND);
	_delay_ms(5);

}


/* 
 * Description : 
 * Clears the RS Pin because a command is being sent
 * Clears the RW Pin to write on the LCD
 * Sends the command to the LCD through Data Pins
 * Sets ENABLE Pin high
 * delay of 2 seconds
 * Clears the ENABLE pin so that data is sent at the falling edge
 */
void LCD_SendCommand(char Data_Value)
{
	DIO_voidSetPinValue(CTRL_PORT, LCD_RS_PIN, PIN_LOW);
	DIO_voidSetPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	DIO_voidSetPinValue (DATA_PORT,	LCD_D0_PIN ,  GET_BIT(Data_Value,0)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D1_PIN ,  GET_BIT(Data_Value,1)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D2_PIN ,  GET_BIT(Data_Value,2)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D3_PIN ,  GET_BIT(Data_Value,3)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D4_PIN ,  GET_BIT(Data_Value,4)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D5_PIN ,  GET_BIT(Data_Value,5)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D6_PIN ,  GET_BIT(Data_Value,6)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D7_PIN ,  GET_BIT(Data_Value,7)   );
	DIO_voidSetPinValue(CTRL_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(CTRL_PORT, LCD_EN_PIN, PIN_LOW);
}


/* 
 * Description : 
 * Sets the RS Pin because data is being sent
 * Clears the RW Pin to write on the LCD
 * Sends the character to be displayed on the LCD
 * Sets ENABLE Pin high
 * delay of 2 seconds
 * Clears the ENABLE pin so that data is sent at the falling edge
 */
void LCD_voidSendData(char character)
{
	DIO_voidSetPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	DIO_voidSetPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	DIO_voidSetPinValue (DATA_PORT,	LCD_D0_PIN ,  GET_BIT(character,0)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D1_PIN ,  GET_BIT(character,1)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D2_PIN ,  GET_BIT(character,2)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D3_PIN ,  GET_BIT(character,3)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D4_PIN ,  GET_BIT(character,4)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D5_PIN ,  GET_BIT(character,5)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D6_PIN ,  GET_BIT(character,6)   );
	DIO_voidSetPinValue (DATA_PORT,	LCD_D7_PIN ,  GET_BIT(character,7)   );
	DIO_voidSetPinValue(CTRL_PORT, LCD_EN_PIN, PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(CTRL_PORT, LCD_EN_PIN, PIN_LOW);
}


/* 
 * Description : 
 * Sends each character in the string to be printed on the LCD 
 */
void LCD_voidSendString(char *str)
{
	
	while(*str)
	{
		LCD_voidSendData(*str);
		str++;
	}
}

void LCD_voidClearScreen(void)
{
			LCD_SendCommand(LCD_CLEAR_CMND);
}
/* 
 * Description : 
 * Converts the floating distance into a string and stores it in str_distance
 */
void ConvertFloatToStr(u16 temp,char *str)
{
	temp = sprintf(str, "%d", temp);
}

void LCD_voidJumpTo2ndLine(void)
{
	u8 i;
	for(i = 12 ; i < 39 ; i++)
	{
		LCD_voidSendData(' ');
	}
}

/* 
 * Description : 
 * Prints to the LCD the distance travelled from the starting point 
 * of the trajectory in the following format : 
 * "Distance = %f"
 */
void Print_Distance_To_LCD(f32 distance)
{
	char str_distance[20]={0};
	ConvertFloatToStr(distance, str_distance);
	LCD_voidSendString(str_distance);
}

void LCD_voidSetCursor(u8 row, u8 col)
{
    u8 address;
		if (col >= 40)
    {
        col = 39;  // Clamp to maximum column value
    }
		
		// Ensure row is within the valid range (0-1 for 2-line LCD)
    if (row > 1)
    {
        row = 0;  // Default to the first row for invalid row values
    }
    switch (row)
    {
    case 0:
        address = col;
        break;
    case 1:
        address = col + 0x40;
        break;
    // Add cases for more rows if you have a larger LCD
    default:
        address = 0;
        break;
    }

    LCD_SendCommand(0x80 | address);  // Set DDRAM address command
		_delay_ms(1);
}

void LCD_voidDeleteCharacters(u8 row, u8 col, u8 length) {
	u8 i;
    LCD_voidSetCursor(row, col);  // Position the cursor
    for (i = 0; i < length; i++) {
        LCD_voidSendData(' ');    // Overwrite with spaces
    }
}

void LCD_voidCursorOff()
{
	LCD_SendCommand(LCD_CURSOR_OFF_CMND);
}
