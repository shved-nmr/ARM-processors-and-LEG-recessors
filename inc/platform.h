/*
 * platform.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <cstdint>


typedef struct {
	bool limitXLow;
	bool limitXHigh;
	bool limitYLow;
	bool limitYHigh;
} LimitSwitches_t;


#define DIRECTION_CLOCKWISE 0
#define DIRECTION_COUNTERCLOCKWISE 1

extern unsigned int X_LENGTH;
extern unsigned int Y_LENGTH;
extern uint8_t X_DIRECTION;
extern uint8_t Y_DIRECTION;

extern uint8_t PLOTTING_SPEED;
extern uint8_t PEN_UP;
extern uint8_t PEN_DOWN;


LimitSwitches_t getLimitSwitches();


#endif /* PLATFORM_H_ */
