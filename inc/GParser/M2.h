/*
 * M2.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef M2_H_
#define M2_H_

#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M2 : public GCode {
public:
	M2(const char* line);
	~M2() = default;
	const char* getType() const override;
	const char* getReply() const override;

	uint8_t getPenUp() const;
	uint8_t getPenDown() const;

protected:
	uint8_t penUp;
	uint8_t penDown;

};


#endif /* M2_H_ */
