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
#include "M10.h"
#include "M11.h"


class GLine {
public:
	GLine (char* line);
	~GLine();

protected:
	GCode* code;
};


#endif /* GPARSER_GLINE_H_ */
