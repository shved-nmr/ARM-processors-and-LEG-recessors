/*
 * platform.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */


#include "platform.h"

unsigned int X_LENGTH {310};
unsigned int Y_LENGTH {380};
uint8_t X_DIRECTION {DIRECTION_CLOCKWISE};
uint8_t Y_DIRECTION {DIRECTION_CLOCKWISE};

uint8_t PLOTTING_SPEED {80};
uint8_t PEN_UP {160};
uint8_t PEN_DOWN {90};

LimitSwitches_t getLimitSwitches() {
	return LimitSwitches_t {true, true, true, true};
}
