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


const char* G28::getType() const {
	return "G28";
}

