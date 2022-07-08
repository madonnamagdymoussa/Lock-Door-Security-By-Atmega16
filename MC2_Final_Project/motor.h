/*
 * motor.h
 *
 *  Created on: Nov 4, 2021
 *      Author: future
 */

#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum{
	DC_CW,
	DC_ACW,
	DC_STOP

}DcMotorState_t;

/* possible states for the dc motor */
void DcMotor_Rotate(DcMotorState_t state);
void DcMotor_Init(void);

#endif /* MOTOR_H_ */
