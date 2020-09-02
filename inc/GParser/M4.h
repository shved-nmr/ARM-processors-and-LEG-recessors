/*
 * M4.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_M4_H_
#define GPARSER_M4_H_


#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M4 : public GCode {
public:
	M4(const char* line);
	~M4() = default;

	const char* getType() const override;

	uint8_t getPower() const;

protected:
	uint8_t power;
};


#endif /* GPARSER_M4_H_ */
