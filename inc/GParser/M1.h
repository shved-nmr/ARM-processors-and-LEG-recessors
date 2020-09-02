/*
 * M1.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef M1_H_
#define M1_H_

#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M1 : public GCode {
public:
	M1(const char* line);
	~M1() = default;

	const char* getType() const override;

	uint8_t getPenPosition() const;

protected:
	uint8_t penPosition;
};


#endif /* M1_H_ */
