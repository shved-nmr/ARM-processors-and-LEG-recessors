/*
 * G1.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#include "GParser/G1.h"


G1::G1(const char* line) {
	sscanf(line, "G1 X%f Y%f A%hhu ",
			&xCoord, &yCoord, &relative);
	this->reply = (char*)"OK\r\n";
}


G1* G1::clone() const {
	auto code = new G1(*this);
	return code;
}


void G1::execute() const {
#ifndef DRY_RUN
	// Move the extruder
#endif
}


const GCode::CodeType G1::getType() const {
	return GCode::CodeType::G1;
}


float G1::getXCoord() const {
	return this->xCoord;
}


float G1::getYCoord() const {
	return this->yCoord;
}


bool G1::isRelative() const {
	return (bool)this->relative;
}

