/*
 * ADC.c
 *
 * Created: 6/12/2024 1:12:13 PM
 *  Author: Jana Wael
 */ 

#include "avr/io.h"
#include "ADC.h"
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "avr/delay.h"
void ADC_Init(void)
{
	/*Define Vref for ADC, as AVCC*/
	SET_BIT(ADMUX, REFS0);
	CLR_BIT(ADMUX, REFS1);
	/*Right Adjust*/
	CLR_BIT(ADMUX, ADLAR);
	/*Choose channel*/
	CLR_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	/*Auto Trigger Mode*/
	SET_BIT(ADCSRA, ADATE);
	/*Define Prescalar*/
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
	/*Enable ADC*/
	SET_BIT(ADCSRA, ADEN);
}
u16 ADC_Read(void)
{
	u16 var = 0;
	/*Start Conversion*/
	SET_BIT(ADCSRA, ADSC);
	/*Wait and check till flag is one, Polling*/
	while(GET_BIT(ADCSRA, ADIF) != 1);
	/*Return value*/
	var = ADCW;
	return var;
}