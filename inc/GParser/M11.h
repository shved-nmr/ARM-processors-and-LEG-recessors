/*
 * M11.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_M11_H_
#define GPARSER_M11_H_

#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M11 : public GCode {
public:
	M11();
	~M11();
	const char* getType() const override;
	const char* getReply() const override;

protected:

};


#endif /* GPARSER_M10_H_ */
