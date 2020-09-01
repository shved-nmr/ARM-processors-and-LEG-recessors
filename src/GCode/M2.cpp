/*
 * M2.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include "GParser/M2.h"


M2::M2(const char* line) {
	sscanf(line, "M2 U%hhu D%hhu ", &PEN_UP, &PEN_DOWN);
	this->reply = (char*)"OK\r\n";
}


const char* M2::getType() const {
	return "M2";
}


const char* M2::getReply() const {
	return this->reply;
}
