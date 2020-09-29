/*
 * platform.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_


#include <cstdint>

#include "board.h"

#include "plotter.h"
#include "servo.h"
#include "pwm.h"


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


// Settings
// Getters
LimitSwitches_t getLimitSwitches();
unsigned int getXLength();
unsigned int getYLength();
Direction getXDirection();
Direction getYDirection();
uint8_t getPlottingSpeed();
uint8_t getPenUp();
uint8_t getPenDown();

// Setters
void setXLength(unsigned int len);
void setYLength(unsigned int len);
void setXDirection(Direction dir);
void setYDirection(Direction dir);
void setPlottingSpeed(uint8_t spd);
void setPenUp(uint8_t val);
void setPenDown(uint8_t val);

// Platform calls
void platform_init();
void setPenPosition(uint8_t val);
void setLaserPower(uint8_t power);
void moveExtruderTo(float x, float y);
void moveExtruderHome();


#endif /* PLATFORM_H_ */
