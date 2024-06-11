/*
 * BUZZER.h
 *
 * Created: 6/10/2024 11:54:13 PM
 *  Author: hp
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/DIO.h"

#define BUZZER_PORT		PORTB_ID
#define BUZZER_PIN		PIN5_ID

void BUZZER_Init();
void BUZZER_ON();
void BUZZER_OFF();

#endif /* BUZZER_H_ */