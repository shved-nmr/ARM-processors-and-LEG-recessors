/*
 * M10.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_M10_H_
#define GPARSER_M10_H_


#include "GCode.h"
#include <cstdio>


class M10 : public GCode {
public:
	M10();
	~M10();
	const char* getType() const override;
	const char* getReply() const override;

protected:

};


#endif /* GPARSER_M10_H_ */
