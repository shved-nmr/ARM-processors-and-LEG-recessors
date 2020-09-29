/*
 * GCode.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_GCODE_H_
#define GPARSER_GCODE_H_


#include "config.h"
#include "platform.h"


class GCode {
public:
	virtual ~GCode() = default;

	enum CodeType {
		G1,
		G28,
		M1,
		M2,
		M4,
		M5,
		M10,
		M11
	};

	virtual GCode* clone() const = 0;
	virtual void execute() const = 0;

	virtual const CodeType getType() const = 0;
	const char* getReply() const;

protected:
	char* reply;
};


#endif /* GPARSER_GCODE_H_ */
