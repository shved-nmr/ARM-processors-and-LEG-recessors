/*
 * Parser.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_GLINE_H_
#define GPARSER_GLINE_H_

#include <cstring>

#include "GCode.h"
#include "G1.h"
#include "G28.h"
#include "M1.h"
#include "M2.h"
#include "M4.h"
#include "M5.h"
#include "M10.h"
#include "M11.h"


class GLine {
public:
	GLine(const char* line);
	GLine(GCode* code);
	GLine(const GLine& line);
	~GLine();

	GLine& operator=(const GLine& line);

	const GCode* getCode() const;

protected:
	GCode* code;
};


#endif /* GPARSER_GLINE_H_ */
