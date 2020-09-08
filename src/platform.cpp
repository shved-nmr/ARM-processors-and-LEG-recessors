/*
 * platform.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */


#include "platform.h"


static unsigned int X_LENGTH {310};
static unsigned int Y_LENGTH {380};
static Direction X_DIRECTION {Direction::clockwise};
static Direction Y_DIRECTION {Direction::counterClockwise};

static uint8_t PLOTTING_SPEED {80};
static uint8_t PEN_UP {160};
static uint8_t PEN_DOWN {90};
static uint8_t PEN_POSITION {PEN_UP};


// Getters
LimitSwitches_t getLimitSwitches() {
	return LimitSwitches_t {true, true, true, true};
}


unsigned int getXLength() {
	return X_LENGTH;
}


unsigned int getYLength() {
	return Y_LENGTH;
}


Direction getXDirection() {
	return X_DIRECTION;
}


Direction getYDirection() {
	return Y_DIRECTION;
}


uint8_t getPlottingSpeed() {
	return PLOTTING_SPEED;
}


uint8_t getPenUp() {
	return PEN_UP;
}


uint8_t getPenDown() {
	return PEN_DOWN;
}


uint8_t getPenPosition() {
	return PEN_POSITION;
}


// Setters
void setXLength(unsigned int len) {
	X_LENGTH = len;
}


void setYLength(unsigned int len) {
	Y_LENGTH = len;
}


void setXDirection(Direction dir) {
	X_DIRECTION = dir;
}


void setYDirection(Direction dir) {
	Y_DIRECTION = dir;
}


void setPlottingSpeed(uint8_t spd) {
	PLOTTING_SPEED = spd;
}


void setPenUp(uint8_t val) {
	PEN_UP = val;
}


void setPenDown(uint8_t val) {
	PEN_DOWN = val;
}


void setPenPosition(uint8_t val) {
	PEN_POSITION = val;
}


void setLaserPower(uint8_t power) {

}

