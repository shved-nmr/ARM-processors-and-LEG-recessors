/*
 * G1.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_G1_H_
#define GPARSER_G1_H_


#include <cstdio>

#include "platform.h"
#include "GCode.h"


class G1 : public GCode {
public:
	G1(const char* line);
	~G1() = default;

	const char* getType() const override;

	float getXCoord() const;
	float getYCoord() const;
	bool isRelative() const;

protected:
	float xCoord;
	float yCoord;
	bool relative;
};


#endif /* GPARSER_G1_H_ */
