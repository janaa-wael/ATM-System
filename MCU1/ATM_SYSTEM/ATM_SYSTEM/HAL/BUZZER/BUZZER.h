/*
 * BUZZER.h
 *
 * Created: 6/10/2024 11:54:13 PM
 *  Author: Jana Wael
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/DIO.h"

#define NUM_OF_BUZZERS		3

#define BUZZER_WARNING		0
#define BUZZER_PROCEEDING	1
#define BUZZER_DEPOSITING	2

void BUZZER_Init();
void BUZZER_ON(u8 BUZZER_ID);
void BUZZER_OFF(u8 BUZZER_ID);
void BUZZER_TOGGLE(u8 BUZZER_ID);

#endif /* BUZZER_H_ */