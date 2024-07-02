/*
 * DC_MOTOR.h
 *
 * Created: 6/14/2024 3:24:50 AM
 *  Author: hp
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"

#define MOTOR1						1
#define MOTOR2						2
#define MOTOR3						3

#define MOTOR1_DRIVE_PORT			PORTB_ID
#define IN1							PIN0_ID
#define IN2							PIN1_ID
#define EN1							PIN3_ID

#define MOTOR2_DRIVE_PORT			PORTD_ID
#define IN3							PIN3_ID
#define IN4							PIN6_ID
#define EN2							PIN7_ID

#define MOTOR3_DRIVE_PORT			PORTA_ID
#define MOTOR3_DRIVE_PIN			PIN7_ID

#define CLOCKWISE_DIR				0
#define ANTIOCLOCKWISE_DIR			1

void MOTORS_voidInit();
void MOTOR_voidSetDirection(u8 MOTOR, u8 direction);
void MOTOR_voidSetMotorSpeed(u8 MOTOR, u8 speed);



#endif /* DC_MOTOR_H_ */