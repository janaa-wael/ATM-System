/*
 * ATM_SYSTEM_MCU2.c
 *
 * Created: 6/13/2024 11:52:10 PM
 * Author : Jana Wael
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#include "../Lib/STD_TYPES.h"
#include "../Lib/BIT_MATH.h"
#include "../MCAL/Timer/Timer.h"
#include "../HAL/DC MOTOR/DC_MOTOR.h"

int main() {
	PWM_voidInit(); // Initialize PWM
	MOTORS_voidInit(); // Initialize motor control pins

	while(1) {
		MOTOR1_voidSetDirection(CLOCKWISE_DIR); // Set direction
		MOTOR2_voidSetDirection(ANTIOCLOCKWISE_DIR);
		for(uint8_t i = 0; i < 255; i++) {
			PWM_voidSetDutyCycle_OC0(i); // Increase speed
			PWM_voidSetDutyCycle_OC2(i);
			_delay_ms(10);
		}
		for(uint8_t i = 255; i > 0; i--) {
			PWM_voidSetDutyCycle_OC0(i); // Decrease speed
			PWM_voidSetDutyCycle_OC2(i);
			_delay_ms(10);
		}

		MOTOR1_voidSetDirection(ANTIOCLOCKWISE_DIR); // Change direction
		MOTOR2_voidSetDirection(CLOCKWISE_DIR);
		for(uint8_t i = 0; i < 255; i++) {
			PWM_voidSetDutyCycle_OC0(i); // Increase speed
			PWM_voidSetDutyCycle_OC2(i);
			_delay_ms(10);
		}
		for(uint8_t i = 255; i > 0; i--) {
			PWM_voidSetDutyCycle_OC0(i); // Decrease speed
			PWM_voidSetDutyCycle_OC2(i);
			_delay_ms(10);
		}
	}
}

