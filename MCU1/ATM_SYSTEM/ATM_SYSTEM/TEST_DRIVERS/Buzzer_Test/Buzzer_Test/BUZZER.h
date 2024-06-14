/*
 * BUZZER.h
 *
 * Created: 6/10/2024 11:54:13 PM
 *  Author: hp
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "DIO.h"

#define BUZZER_PORT		PORTB_ID
#define BUZZER_PIN		PIN3_ID

void BUZZER_Init();
void BUZZER_ON();
void BUZZER_OFF();
void BUZZER_TOGGLE();

#endif /* BUZZER_H_ */