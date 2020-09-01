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
	snprintf(this->reply, 80, "M11 %i %i %i %i\r\nOK\r\n",
			switches.limitYHigh, switches.limitYLow,
			switches.limitXHigh, switches.limitXLow);
}


const char* M11::getType() const {
	return "M11";
}


const char* M11::getReply() const {
	return this->reply;
}


M11::~M11() {
	delete[] (this->reply);
}
