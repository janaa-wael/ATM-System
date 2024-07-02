/*
 * ADC.h
 *
 * Created: 6/12/2024 1:12:24 PM
 *  Author: Jana Wael
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../Lib/STD_TYPES.h"
#include <avr/io.h>

void ADC_Init(void);
u16 ADC_Read(void);

#endif /* ADC_H_ */