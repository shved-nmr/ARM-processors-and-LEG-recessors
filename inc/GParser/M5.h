/*
 * M5.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_M5_H_
#define GPARSER_M5_H_


#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M5 : public GCode {
public:
	M5(const char* line);
	~M5() = default;
	const char* getType() const override;
	const char* getReply() const override;

	unsigned int getXLength() const;
	unsigned int getYLength() const;
	uint8_t getXDirection() const;
	uint8_t getYDirection() const;
	uint8_t getPlottingSpeed() const;

protected:
	unsigned int xLength;
	unsigned int yLength;
	uint8_t xDirection;
	uint8_t yDirection;
	uint8_t plottingSpeed;
};


#endif /* GPARSER_M5_H_ */
