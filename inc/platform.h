/*
 * platform.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <cstdint>


enum Direction {
	clockwise = 0,
	counterClockwise = 1
};


typedef struct {
	bool limitXLow;
	bool limitXHigh;
	bool limitYLow;
	bool limitYHigh;
} LimitSwitches_t;


extern unsigned int X_LENGTH;
extern unsigned int Y_LENGTH;
extern Direction X_DIRECTION;
extern Direction Y_DIRECTION;

extern uint8_t PLOTTING_SPEED;
extern uint8_t PEN_UP;
extern uint8_t PEN_DOWN;
extern uint8_t PEN_POSITION;


LimitSwitches_t getLimitSwitches();


#endif /* PLATFORM_H_ */
