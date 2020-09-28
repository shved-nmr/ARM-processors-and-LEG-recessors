/*
 * pwm.h
 *
 *  Created on: Sep 26, 2020
 *      Author: MStefan99
 */

#ifndef PWM_H_
#define PWM_H_


#include <cstdint>

#include <board.h>


void pwm_enable(uint8_t channel, uint8_t port, uint8_t pin);  // Call to enable PWM output on the pin. This will disable GPIO function
void pwm_disable(uint8_t channel);  // Call to disable PWM and use GPIO function again
void pwm_setFreq(uint8_t channel, uint32_t freq); // Call this to set PWM frequency in Hz. Channels 0-2 and 3-5 share the same frequency
void pwm_setDuty(uint8_t channel, uint8_t duty);  // Call this to set duty cycle in range 0 - 255


#endif /* PWM_H_ */
