/*
 * ADC.h
 *
 * Created: 6/12/2024 1:12:24 PM
 *  Author: Jana Wael
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../Lib/STD_TYPES.h"

#define SREG  *((volatile u8*)0x5F) //status register----------------global interupt enable
#define SREG_I    7





#define ADMUX				*((volatile u8*)0x27)		//ADC multiplexer selection register
/* ADMUX Bits   */
#define ADMUX_REFS1         7							//Reference selection bit1
#define ADMUX_REFS0         6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC left adjust result



#define ADCSRA				*((volatile u8*)0x26)		//ADC control and status register A
/* ADSRA Bits   */
#define ADCSRA_ADEN			7							//ADC enable
#define ADCSRA_ADSC			6                           //Start conversion
#define ADCSRA_ADATE	    5                           //Auto trigger enable
#define ADCSRA_ADIF			4                           //Interrupt flag
#define ADCSRA_ADIE			3                           //Interrupt enable
#define ADCSRA_ADPS2	    2                       //Prescaler bit2
#define ADCSRA_ADPS1	    1                       //Prescaler bit1
#define ADCSRA_ADPS0	    0                       //Prescaler bit0


/* Data Reg  */
#define ADCH				*((volatile u8*)0x25)		//ADC high register
#define ADCL				*((volatile u8*)0x24)		//ADC Low register
#define ADC_u16_ADC_REG           *((volatile u16 *)0x24)		//ADC Low + High


#define SFIOR  *((volatile u8 *)0x50)
/* SFIOR Bits   */
#define SFIOR_ADTS2			7                          //Trigger Source bit2
#define SFIOR_ADTS1	     	6                          //Trigger Source bit1
#define SFIOR_ADTS0		    5                          //Trigger Source bit0

#define ADC_u32_TIME_OUT_MAX_VALUE            50000

#define ADC_u8_CHANNEL_0                  0
#define ADC_u8_CHANNEL_1                  1
#define ADC_u8_CHANNEL_2                  2
#define ADC_u8_CHANNEL_3                  3
#define ADC_u8_CHANNEL_4                  4
#define ADC_u8_CHANNEL_5                  5
#define ADC_u8_CHANNEL_6                  6
#define ADC_u8_CHANNEL_7                  7

void   ADC_voidInit(void);

u16     ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNb);

void   ADC_voidGetDigitalValueAsynch          (u8 Copy_u8ChannelNb,void(*Copy_pfNotification)(u16));

void   ADC_u8GetADCRegValue                 (u16 * Copy_pu16ADCValue);

#endif /* ADC_H_ */