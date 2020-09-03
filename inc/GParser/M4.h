/*
 * M4.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_M4_H_
#define GPARSER_M4_H_


#include <cstdio>
#include <cstring>

#include "platform.h"
#include "GCode.h"


class M4 : public GCode {
public:
	M4(const char* line);
	~M4() = default;

	M4* clone() const override;
	void execute() const override;

	const char* getType() const override;

	uint8_t getPower() const;

protected:
	uint8_t power;
};


#endif /* GPARSER_M4_H_ */
