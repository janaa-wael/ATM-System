/*
 * DC_MOTOR.c
 *
 * Created: 6/14/2024 3:24:03 AM
 *  Author: Jana Wael
 */ 

#include "../../Lib/BIT_MATH.h"
#include "../../Lib/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/DIO/DIO.h"

#include "DC_MOTOR.h"

void MOTORS_voidInit()
{
	DIO_voidSetPortDirection(MOTOR1_DRIVE_PORT,PORT_OUTPUT);
	DIO_voidSetPortDirection(MOTOR2_DRIVE_PORT,PORT_OUTPUT);
	DIO_voidSetPortDirection(MOTOR3_DRIVE_PORT,PORT_OUTPUT);
}

void MOTOR_voidSetDirection(u8 MOTOR, u8 direction)
{
	if(MOTOR == MOTOR1)
	{
			if(direction == CLOCKWISE_DIR)
			{
				DIO_voidSetPinValue(MOTOR1_DRIVE_PORT,IN1,PIN_HIGH);
				DIO_voidSetPinValue(MOTOR1_DRIVE_PORT,IN2,PIN_LOW);
			}
			else
			{
				DIO_voidSetPinValue(MOTOR1_DRIVE_PORT,IN2,PIN_HIGH);
				DIO_voidSetPinValue(MOTOR1_DRIVE_PORT,IN1,PIN_LOW);
			}
	}
	else if(MOTOR == MOTOR2)
	{
			if(direction == CLOCKWISE_DIR)
			{
				DIO_voidSetPinValue(MOTOR2_DRIVE_PORT,IN3,PIN_HIGH);
				DIO_voidSetPinValue(MOTOR2_DRIVE_PORT,IN4,PIN_LOW);
			}
			else
			{
				DIO_voidSetPinValue(MOTOR2_DRIVE_PORT,IN3,PIN_LOW);
				DIO_voidSetPinValue(MOTOR2_DRIVE_PORT,IN4,PIN_HIGH);
			}
	}
}

void MOTOR_voidSetMotorSpeed(u8 MOTOR, u8 speed)
{
	if(MOTOR == MOTOR1)
		PWM_voidSetDutyCycle_OC0(speed);
	else if(MOTOR == MOTOR2)
		PWM_voidSetDutyCycle_OC2(speed);
}

