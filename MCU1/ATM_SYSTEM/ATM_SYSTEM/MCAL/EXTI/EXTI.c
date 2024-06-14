/*
 * EXTI.c
 *
 * Created: 3/7/2024 12:41:13 AM
 *  Author: Jana Wael
 */ 

#include "EXTI.h"
#include "../../Lib/BIT_MATH.h" /* To use the macros like SET_BIT */
#include "../../Lib/STD_TYPES.h"
#include "../DIO/DIO.h"

void (*EXTI_CallBack[3])()={NULL};


void EXTI_void_GLOABALINT_ENAB()
{
	SET_BIT(SREG,SREG_I);
}

void EXTI_void_Int0_Init(u8 Copy_u8Sense_Control)
{
	switch(Copy_u8Sense_Control){  //select the mode

		case LOW_LEVEL :             
			CLR_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case LOGICAL_CHANGE :        
			SET_BIT(MCUCR,MCUCR_ISC00);
			CLR_BIT(MCUCR,MCUCR_ISC01);
			break;
		case FALLNG_EDGE :           
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
		case RISING_EDGE :				
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
			break;
	}
	SET_BIT(GICR,GICR_INT0); // Enable the interupt
}

void EXTI_void_Int1_Init(u8 Copy_u8Sense_Control)
{
	switch(Copy_u8Sense_Control){

		case LOW_LEVEL :             
			CLR_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		
		case LOGICAL_CHANGE :        
			SET_BIT(MCUCR,MCUCR_ISC10);
			CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
		
		case FALLNG_EDGE :           
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		
		case RISING_EDGE :           
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
			break;
	}
	SET_BIT(GICR,GICR_INT1);
	
}

void EXTI_void_Int2_Init(u8 Copy_u8Sense_Control)
{
	switch(Copy_u8Sense_Control){

		case FALLNG_EDGE :           
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		
		case RISING_EDGE :           
			SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
	}
	SET_BIT(GICR,GICR_INT2);
}


void EXTI_voidDisableInterrupt   ( u8 Copy_u8INT_Number )
{

	if ( (Copy_u8INT_Number>=GICR_INT2) && (Copy_u8INT_Number<=GICR_INT1) )  /* Check [5:7] */
	{
		/* Clear The Required BIT */
		CLR_BIT( GICR , Copy_u8INT_Number );
	}

	
}


u8 EXTI_u8GetFlag( u8 Copy_u8INT_Number )
{
	
	return GET_BIT( GIFR , Copy_u8INT_Number );
	
}

void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8EXTILine )
{

	if( Copy_pvoidCallBack != NULL ){
		switch(Copy_u8EXTILine)
		{
			case INT0 : EXTI_CallBack[0] = Copy_pvoidCallBack ; break;
			case INT1 : EXTI_CallBack[1] = Copy_pvoidCallBack ; break;
			case INT2 : EXTI_CallBack[2] = Copy_pvoidCallBack ; break;
			
		}

		

	}

}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if( EXTI_CallBack[0] != NULL ){

		EXTI_CallBack[0](); /*  Call The Global Pointer to Func   */


	}

}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{

	if( EXTI_CallBack[1] != NULL ){

		EXTI_CallBack[1]();
		

	}

}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{

	if( EXTI_CallBack[2] != NULL ){

		EXTI_CallBack[2]();
		

	}

}