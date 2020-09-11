/*
 * M5.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */


#include "GParser/M5.h"


M5::M5(const char* line) {
	sscanf(line, "M5 A%hhu B%hhu H%u W%u S%hhu ",
			&xDirection, &yDirection,
			&yLength, &xLength, &plottingSpeed);
	this->reply = (char*)"OK\r\n";
}


M5* M5::clone() const {
	auto code = new M5(*this);
	return code;
}


void M5::execute() const {
	setXLength(this->xLength);
	setYLength(this->yLength);
	setXDirection((Direction)this->xDirection);
	setYDirection((Direction)this->yDirection);
	setPlottingSpeed(this->plottingSpeed);

#ifndef DRY_RUN
	// Nothing to do
#endif
}


const char* M5::getType() const {
	return "M5";
}


unsigned int M5::getXLength() const {
	return this->xLength;
}


unsigned int M5::getYLength() const {
	return this->yLength;
}


Direction M5::getXDirection() const {
	return (Direction) this->xDirection;
}


Direction M5::getYDirection() const {
	return (Direction) this->yDirection;
}


uint8_t M5::getPlottingSpeed() const {
	return this->plottingSpeed;
}

