/*
 * M5.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef M5_H_
#define M5_H_


#include <cstdio>
#include <cstring>

#include "platform.h"
#include "GCode.h"


class M5 : public GCode {
public:
	M5(const char* line);
	~M5() = default;

	M5* clone() const override;
	void execute() const override;

	const GCode::CodeType getType() const override;

	unsigned int getXLength() const;
	unsigned int getYLength() const;
	Direction getXDirection() const;
	Direction getYDirection() const;
	uint8_t getPlottingSpeed() const;

protected:
	unsigned int xLength;
	unsigned int yLength;
	uint8_t xDirection;
	uint8_t yDirection;
	uint8_t plottingSpeed;
};


#endif /* M5_H_ */
