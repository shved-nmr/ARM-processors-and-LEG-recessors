/*
 * Parser.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include <GParser/GLine.h>


GLine::GLine(char* line) {
	if (strstr(line, "M10")) {
		this->code = new M10();
	}
}


GLine::~GLine() {
	delete (this->code);
}
