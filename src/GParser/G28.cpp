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


void G28::execute() const {
#ifndef DRY_RUN
	moveExtruderHome();
#endif
}


const GCode::CodeType G28::getType() const {
	return GCode::CodeType::G28;
}

