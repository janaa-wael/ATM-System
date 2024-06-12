/*
 * BIT_MATH.h
 *
 * Created: 2/2/2024 8:19:31 PM
 *  Author: Jana Wael
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))



#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )

#endif