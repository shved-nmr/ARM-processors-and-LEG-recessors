/*
 * M10.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M10.h"


M10::M10() {
	this->reply = new char[80];
	snprintf(this->reply, 80, "M10 XY %i %i 0.00 0.00 A%i B%i S%i H0 U%i D%i\r\nOK\r\n",
			Y_LENGTH, X_LENGTH, X_DIRECTION, Y_DIRECTION,
			PLOTTING_SPEED, PEN_UP, PEN_DOWN);
}


const char* M10::getType() const {
	return "M10";
}


const char* M10::getReply() const {
	return this->reply;
}

M10::~M10() {
	delete[] (this->reply);
}

