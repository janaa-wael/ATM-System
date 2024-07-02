/*
 * UART.h
 *
 * Created: 6/30/2024 5:49:37 PM
 *  Author: hp
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"

void UART_init(u32 baud_rate);
void UART_sendByte(const u8 data);
u8 UART_recieveByte(void);
void UART_sendString(const u8 *Str);
void UART_receiveString(u8 *Str); // Receive until 

#endif /* UART_H_ */