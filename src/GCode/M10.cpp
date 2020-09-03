/*
 * M10.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M10.h"


M10::M10() {
	this->reply = new char[80];
	snprintf(this->reply, 79, "M10 XY %i %i 0.00 0.00 A%i B%i S%i H0 U%i D%i\r\nOK\r\n",
			getYLength(), getXLength(),
			getXDirection(), getYDirection(),
			getPlottingSpeed(), getPenUp(), getPenDown());
}


M10* M10::clone() const {
	auto code = new M10(*this);
	code->reply = new char[80];
	strncpy(code->reply, this->reply, 79);
	return code;
}


void M10::execute() const {
#ifndef DRY_RUN
	// Nothing to do
#endif
}


const char* M10::getType() const {
	return "M10";
}


M10::~M10() {
	delete[] (this->reply);
}

