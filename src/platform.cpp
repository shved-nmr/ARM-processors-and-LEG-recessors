/*
 * platform.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */


#include "platform.h"


unsigned int X_LENGTH {310};
unsigned int Y_LENGTH {380};
Direction X_DIRECTION {Direction::clockwise};
Direction Y_DIRECTION {Direction::counterClockwise};

uint8_t PLOTTING_SPEED {80};
uint8_t PEN_UP {160};
uint8_t PEN_DOWN {90};
uint8_t PEN_POSITION {PEN_UP};


LimitSwitches_t getLimitSwitches() {
	return LimitSwitches_t {true, true, true, true};
}

