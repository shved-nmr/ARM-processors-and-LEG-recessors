/*
 * M11.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M11.h"


M11::M11() {
	this->reply = new char[80];
	auto switches {getLimitSwitches()};
	snprintf(this->reply, 79, "M11 %i %i %i %i\r\nOK\r\n",
			switches.limitYHigh, switches.limitYLow,
			switches.limitXHigh, switches.limitXLow);
}


M11* M11::clone() const {
	auto code = new M11(*this);
	code->reply = new char[80];
	strncpy(code->reply, this->reply, 79);
	return code;
}


void M11::execute() const {
	// Nothing to do
}


const GCode::CodeType M11::getType() const {
	return GCode::CodeType::M11;
}


M11::~M11() {
	delete[] (this->reply);
}
