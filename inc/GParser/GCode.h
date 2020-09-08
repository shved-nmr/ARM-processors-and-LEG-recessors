/*
 * GCode.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_GCODE_H_
#define GPARSER_GCODE_H_


#include "platform.h"


class GCode {
public:
	virtual ~GCode() = default;

	virtual GCode* clone() const = 0;
	virtual void execute() const = 0;

	virtual const char* getType() const = 0;
	const char* getReply() const;

protected:
	char* reply;
};


#endif /* GPARSER_GCODE_H_ */
