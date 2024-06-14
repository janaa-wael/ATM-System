/*
 * KEYPAD.c
 *
 * Created: 6/9/2024 7:45:13 PM
 *  Author: Jana Wael
 */ 

#include <avr/delay.h>
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "KEYPAD.h"
const u8 KEYPAD [4][4]= KPD_VALUES;

void KEYPAD_voidInit(void)
{
	/*Set the Raw port as input with PORT=1 to activate the internal pull up */
	DIO_voidSetPortDirection(KEYPAD_ROW_PORT,ROW_PORT_INPUT);
	DIO_voidSetPortValue(KEYPAD_ROW_PORT,0x0F);
	/*Set the COL port as output with Initial value =LOGIC HIGH*/ 
    DIO_voidSetPortDirection(KEYPAD_COL_PORT,COL_PORT_OUTPUT);
    DIO_voidSetPortValue(KEYPAD_COL_PORT,0x0F);
}

u8 KEYPAD_READ(void) {
		u8 row = 0;
		u8 col = 0;
    DIO_voidSetPortValue(KEYPAD_COL_PORT,0x0F);
    DIO_voidSetPortValue(KEYPAD_ROW_PORT,0x0F);
    for (col = 0; col < 4; col++) {
        // Drive the current column low
        DIO_voidSetPinValue(KEYPAD_COL_PORT, col, 0);
        for (row = 0; row < 4; row++) {
            u8 val;
            val = DIO_u8GetPinValue(KEYPAD_ROW_PORT, row);
							
            if (val == 0) {
                // Debounce
                _delay_ms(10);  // Assuming you have a delay function
                val = DIO_u8GetPinValue(KEYPAD_ROW_PORT, row);
								
                if (val == 0) {
                    // Wait until the key is released
                    while (val == 0) {
						val = DIO_u8GetPinValue(KEYPAD_ROW_PORT, row);
                    }
                    DIO_voidSetPinValue(KEYPAD_COL_PORT, col, 1); // Reset the column
                    return KEYPAD[row][col];  // Return the corresponding character from the keymap
                }
            }
        }

        // Reset the column back high
        DIO_voidSetPinValue(KEYPAD_COL_PORT, col, 1);
    }
    return 'x';  // Indicate no key press
}
