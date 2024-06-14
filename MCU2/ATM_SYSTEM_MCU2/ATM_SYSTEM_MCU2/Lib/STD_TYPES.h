/*
 * STD_TYPES.h
 *
 * Created: 2/2/2024 4:21:12 AM
 *  Author: Jana Wael
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;



#endif /* STD_TYPES_H_ */

/*

// Function to initialize PWM on Timer0
void pwm_init() {
	// Set Fast PWM mode, non-inverting
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // Fast PWM, Prescaler=8

	// Set PB3 (OC0) as output
	DDRB |= (1 << PB3);
}

// Function to set PWM duty cycle (0-255)
void set_pwm_duty_cycle(uint8_t duty_cycle) {
	OCR0 = duty_cycle;
}


void motor_init() {
	// Set PD0 and PD1 as output
	DDRA |= (1 << PA0) | (1 << PA1);
}

void set_motor_direction(uint8_t direction) {
	if (direction) {
		PORTA |= (1 << PA0);
		PORTA &= ~(1 << PA1);
		} else {
		PORTA |= (1 << PA1);
		PORTA &= ~(1 << PA0);
	}
}

int main() {
	PWM_voidInit(); // Initialize PWM
	MOTOR_voidInit(); // Initialize motor control pins

	while(1) {
		set_motor_direction(1); // Set direction
		for(uint8_t i = 0; i < 255; i++) {
			set_pwm_duty_cycle(i); // Increase speed
			_delay_ms(10);
		}
		for(uint8_t i = 255; i > 0; i--) {
			set_pwm_duty_cycle(i); // Decrease speed
			_delay_ms(10);
		}

		set_motor_direction(0); // Change direction
		for(uint8_t i = 0; i < 255; i++) {
			set_pwm_duty_cycle(i); // Increase speed
			_delay_ms(10);
		}
		for(uint8_t i = 255; i > 0; i--) {
			set_pwm_duty_cycle(i); // Decrease speed
			_delay_ms(10);
		}
	}
}


*/