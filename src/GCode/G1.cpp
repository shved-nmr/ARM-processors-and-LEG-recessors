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


const char* G1::getType() const {
	return "G1";
}


float G1::getXCoord() const {
	return this->xCoord;
}


float G1::getYCoord() const {
	return this->yCoord;
}


bool G1::isRelative() const {
	return this->relative;
}

