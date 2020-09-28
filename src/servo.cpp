/*
 * servo.cpp
 *
 *  Created on: Sep 28, 2020
 *      Author: MStefan99
 */


#include "servo.h"


void servo_enable(uint8_t channel, uint8_t port, uint8_t pin) {
	pwm_enable(channel, port, pin);
	pwm_setFreq(channel, 50);
}


void servo_move(uint8_t channel, uint8_t angle) {
	pwm_setDuty(channel, angle / 20 + 13);
}

