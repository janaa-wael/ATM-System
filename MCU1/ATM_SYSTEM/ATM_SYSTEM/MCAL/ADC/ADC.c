/*
 * ADC.c
 *
 * Created: 6/12/2024 1:12:13 PM
 *  Author: Jana Wael
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "ADC.h"
#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include <avr/delay.h>
#include <stddef.h>

static void(*ADC_pfNotification)(u16) = NULL;
/* ADC busy flag */
static u8 ADC_u8BusyFlag = 0;

void ADC_voidInit(void)
{
	/*	1- Select Vref = AVCC
		2- Right Adjust
		3- Disable AutoTrigger
		4- Select CLK/64
		5- Enable ADC
	 */
	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);
			
	CLR_BIT(ADMUX,ADMUX_ADLAR);

	CLR_BIT(ADCSRA,ADCSRA_ADATE);

	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	CLR_BIT(ADCSRA,ADCSRA_ADPS0);

	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

u16   ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNb)
{
	
	u32 Local_u32TimeOutCounter = 0;
	if((Copy_u8ChannelNb < 32) )
	{
		/* Clear MUX4..0 */
		ADMUX &= 0b11100000;
		/* Select Channel */
		ADMUX |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/* Wait flag = 1 */
		while((GET_BIT(ADCSRA,ADCSRA_ADIF)== 0) && (Local_u32TimeOutCounter < ADC_u32_TIME_OUT_MAX_VALUE))
		{
			Local_u32TimeOutCounter++;
		}
		//while(!GET_BIT(ADCSRA,ADCSRA_ADIF));
		if(GET_BIT(ADCSRA,ADCSRA_ADIF)!= 0)//(Local_u32TimeOutCounter<ADC_u32_TIME_OUT_MAX_VALUE)
		{
			/* Clear flag */
			SET_BIT(ADCSRA,ADCSRA_ADIF);
			/* Read the Digital Value */
			return ADC_u16_ADC_REG;
		}	
	}

	
}
void ADC_voidGetDigitalValueAsynch(u8 Copy_u8ChannelNb,void(*Copy_pfNotification)(u16))
{
	
	if((Copy_u8ChannelNb < 32) && (Copy_pfNotification != NULL) && (ADC_u8BusyFlag == 0))
	{
		
		/* Set Flag to make ADC is Busy */
		ADC_u8BusyFlag = 1;
		/* update Global Pointer to a function */
		ADC_pfNotification = Copy_pfNotification;
		/* Enable ADC Interrupt */
		SET_BIT(ADCSRA,ADCSRA_ADIE);
		SET_BIT(SREG,SREG_I);
		/* Clear MUX4..0 */
		ADMUX &= 0b11100000;
		/* Select Channel */
		ADMUX |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADCSRA,ADCSRA_ADSC);
	}
	
}
void ADC_u8GetADCRegValue(u16 * Copy_pu16ADCValue)
{	
	if(Copy_pu16ADCValue != NULL)
	{
		/* Read ADC Register */
		*Copy_pu16ADCValue = ADC_u16_ADC_REG;
	}
}

/* Prototype for ADC ISR */
void __vector_16(void)     __attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL)
	{
		/* Clear Flag */
		ADC_u8BusyFlag = 0;
		/* Clear PIE of ADC */
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
		/* Calling Notification function */
		ADC_pfNotification(ADC_u16_ADC_REG);
	}
}
