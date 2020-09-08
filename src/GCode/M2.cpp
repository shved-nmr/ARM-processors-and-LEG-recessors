/*
 * M2.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M2.h"


M2::M2(const char* line) {
	sscanf(line, "M2 U%hhu D%hhu ", &penUp, &penDown);
	this->reply = (char*)"OK\r\n";
}


M2* M2::clone() const {
	auto code = new M2(*this);
	return code;
}


void M2::execute() const {
	setPenUp(this->penUp);
	setPenDown(this->penDown);

#ifndef DRY_RUN
	// Nothing to do
#endif
}


const char* M2::getType() const {
	return "M2";
}


uint8_t M2::getPenUp() const {
	return this->penUp;
}


uint8_t M2::getPenDown() const {
	return this->penDown;
}

