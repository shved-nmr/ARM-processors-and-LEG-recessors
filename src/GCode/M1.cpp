/*
 * M1.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M1.h"


M1::M1(const char* line) {
	sscanf(line, "M1 %hhu ", &PEN_POSITION);
	this->reply = (char*)"OK\r\n";
}


const char* M1::getType() const {
	return "M1";
}


const char* M1::getReply() const {
	return this->reply;
}
