/*
 * M4.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#include "GParser/M4.h"


M4::M4(const char* line) {
	sscanf(line, "M4 %hhu ", &power);
	this->reply = (char*)"OK\r\n";
}


M4* M4::clone() const {
	auto code = new M4(*this);
	return code;
}


void M4::execute() const {
#ifndef DRY_RUN
	setLaserPower(this->power);
#endif
}


const char* M4::getType() const {
	return "M4";
}


uint8_t M4::getPower() const {
	return this->power;
}

