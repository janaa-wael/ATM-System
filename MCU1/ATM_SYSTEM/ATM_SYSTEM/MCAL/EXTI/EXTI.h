
/*
 * EXTI.h
 *
 * Created: 3/7/2024 12:40:58 AM
 *  Author: Jana Wael
 */ 

/*************************************/
/********* Name : Jana Wael **********/
/********* Date : 29/2/2024 **********/
/********* SWC : EXTI	    **********/
/********* Version : 1.0    **********/
/*************************************/

#include "../../Lib/STD_TYPES.h"
#ifndef EXTI_H_
#define EXTI_H_

#define SREG  *((volatile u8*)0x5F) //status register----------------global interupt enable
#define SREG_I    7

#define GICR    *((volatile u8*)0x5B) //control the exti enable
#define GICR_INT1     7
#define GICR_INT0     6
#define GICR_INT2     5

#define GIFR    *((volatile u8*)0x5A) //exti flags
#define GIFR_INT1     7
#define GIFR_INT0     6
#define GIFR_INT2     5

#define MCUCR    *((volatile u8*)0x55) //exti0,1 status
#define MCUCR_ISC00     0
#define MCUCR_ISC01     1
#define MCUCR_ISC10     2
#define MCUCR_ISC11     3

#define MCUCSR    *((volatile u8*)0x54) //exti2 status
#define MCUCSR_ISC2     6

#define      LOW_LEVEL        0
#define      LOGICAL_CHANGE   1    
#define      RISING_EDGE      2
#define      FALLNG_EDGE      3

/* Copy_u8INT_Number */
#define INT1     7
#define INT0     6
#define INT2     5




#define      ENABLED         1
#define      DISABLED        0

#define     NULL             0

/*   options:
       1-LOW_LEVEL
       2-LOGICAL_CHANGE
       3-RISING_EDGE
       4-FALLNG_EDGE
             */






void EXTI_void_GLOABALINT_ENAB();

void EXTI_void_Int0_Init(u8 Copy_u8Sense_Control);

void EXTI_void_Int1_Init(u8 Copy_u8Sense_Control);

void EXTI_void_Int2_Init(u8 Copy_u8Sense_Control);

void EXTI_voidDisableInterrupt   ( u8 Copy_u8INT_Number );

u8 EXTI_u8GetFlag( u8 Copy_u8INT_Number );

void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number );


#endif
