/*
 * Parser.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#include <GParser/GLine.h>


GLine::GLine(const char* line) {
	if (strstr(line, "G1")) {
		this->code = new G1(line);
	} else if (strstr(line, "G28")) {
		this->code = new G28();
	} else if (strstr(line, "M1")) {
		this->code = new M1(line);
	} else if (strstr(line, "M2")) {
		this->code = new M2(line);
	} else if (strstr(line, "M4")) {
		this->code = new M4(line);
	} else if (strstr(line, "M5")) {
		this->code = new M5(line);
	} else if (strstr(line, "M10")) {
		this->code = new M10();
	} else if (strstr(line, "M11")) {
		this->code = new M11();
	}
}


const GCode* GLine::getCode() const {
	return this->code;
}


GLine::~GLine() {
	delete (this->code);
}
