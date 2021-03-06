/*
 * M1.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M1.h"


M1::M1(const char* line) {
	sscanf(line, "M1 %hhu ", &penPosition);
	this->reply = (char*)"OK\r\n";
}


M1* M1::clone() const {
	auto code = new M1(*this);
	return code;
}


void M1::execute() const {
#ifndef DRY_RUN
	setPenPosition(this->penPosition);
#endif
}


const GCode::CodeType M1::getType() const {
	return GCode::CodeType::M1;
}


uint8_t M1::getPenPosition() const {
	return this->penPosition;
}
