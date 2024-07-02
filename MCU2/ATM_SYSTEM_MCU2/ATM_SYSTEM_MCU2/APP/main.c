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
#include "../MCAL/UART/UART.h"
#include "../HAL/DC MOTOR/DC_MOTOR.h"

int main() {
	PWM_voidInit(); // Initialize PWM
	MOTORS_voidInit(); // Initialize motor control pins
	UART_init(9600);
	
	while(1) {
		u8 received_byte = UART_recieveByte();
		if(received_byte == 'd')
		{
					MOTOR_voidSetDirection(MOTOR1,CLOCKWISE_DIR); // Set direction
					MOTOR_voidSetDirection(MOTOR2,ANTIOCLOCKWISE_DIR);
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
		else if (received_byte == 'w')
		{
			MOTOR_voidSetDirection(MOTOR1,ANTIOCLOCKWISE_DIR); // Change direction
			MOTOR_voidSetDirection(MOTOR2,CLOCKWISE_DIR);
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
}

