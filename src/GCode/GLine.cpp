/*
 * Parser.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include <GParser/GLine.h>


GLine::GLine(const char* line) {
	if (strstr(line, "M10")) {
		this->code = new M10();
	} else if (strstr(line, "M11")) {
		this->code = new M11();
	} else if (strstr(line, "M2")) {
		this->code = new M2(line);
	}
}


GLine::~GLine() {
	delete (this->code);
}
