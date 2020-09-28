/*
 * servo.h
 *
 *  Created on: Sep 28, 2020
 *      Author: MStefan99
 */

#ifndef SERVO_H_
#define SERVO_H_


#include "pwm.h"


void servo_enable(uint8_t channel, uint8_t port, uint8_t pin);  // Call this to enable servo output. Shares PWM channels
void servo_move(uint8_t channel, uint8_t angle);  // Call to move servo in the range 0 - 255


#endif /* SERVO_H_ */
