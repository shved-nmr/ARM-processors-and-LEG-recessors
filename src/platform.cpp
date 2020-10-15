/*
 * platform.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */


#include "platform.h"


static unsigned int X_LENGTH {150};
static unsigned int Y_LENGTH {100};
static Direction X_DIRECTION {Direction::clockwise};
static Direction Y_DIRECTION {Direction::clockwise};

static uint8_t PLOTTING_SPEED {80};
static uint8_t PEN_UP {160};
static uint8_t PEN_DOWN {90};


// Getters
LimitSwitches_t getLimitSwitches() {
	return plotter_getLimits();
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


// Setters
void setXLength(unsigned int len) {
	X_LENGTH = len;
	plotter_setDim(X_LENGTH, Y_LENGTH);
}


void setYLength(unsigned int len) {
	Y_LENGTH = len;
	plotter_setDim(X_LENGTH, Y_LENGTH);
}


void setXDirection(Direction dir) {
	X_DIRECTION = dir;
	plotter_setDir(X_DIRECTION == Direction::clockwise,
		Y_DIRECTION == Direction::clockwise);  // TODO: check hardware direction
}


void setYDirection(Direction dir) {
	Y_DIRECTION = dir;
	plotter_setDir(X_DIRECTION == Direction::clockwise,
		Y_DIRECTION == Direction::clockwise);  // TODO: check hardware direction
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


// Platform calls
void platform_init() {
	servo_enable(3, 0, 10);

	setLaserPower(0);
	setPenPosition(PEN_UP);

	plotter_setDim(X_LENGTH, Y_LENGTH);
	plotter_setDir(X_DIRECTION == Direction::clockwise,
		Y_DIRECTION == Direction::clockwise);  // TODO: check hardware direction

	plotter_calibrate();
}


void setPenPosition(uint8_t val) {
	servo_move(3, val);
	vTaskDelay(500);
}


void setLaserPower(uint8_t power) {
	if (!power) {
		pwm_disable(0);
		DigitalIoPin {0, 12, DigitalIoPin::pinMode::output} = false;
	} else {
		pwm_enable(0, 0, 12);
		pwm_setFreq(0, 1000);
		pwm_setDuty(0, power);
	}
}


void moveExtruderTo(float x, float y) {
	plotter_moveTo(x, y, PLOTTING_SPEED * 10);
}


void moveExtruderHome() {
	setLaserPower(0);
	setPenPosition(PEN_UP);
	plotter_home();
}


void calibrate() {
	plotter_calibrate();
}

