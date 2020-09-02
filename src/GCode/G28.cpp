/*
 * G28.cpp
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#include "GParser/G28.h"


G28::G28() {
	this->reply = (char*)"OK\r\n";
}


G28* G28::clone() const {
	auto code = new G28(*this);
	return code;
}


const char* G28::getType() const {
	return "G28";
}

