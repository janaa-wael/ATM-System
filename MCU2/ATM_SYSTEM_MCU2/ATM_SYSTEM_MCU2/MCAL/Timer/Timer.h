/*
 * Timer.h
 *
 * Created: 6/14/2024 3:35:03 AM
 *  Author: Jana Wael
 */ 


#ifndef TIMER_H_
#define TIMER_H_

// Function to initialize PWM on Timer0
void PWM_voidInit();
void PWM_voidSetDutyCycle_OC0(u8 duty_cycle);
void PWM_voidSetDutyCycle_OC2(u16 duty_cycle);


#endif /* TIMER_H_ */