/*
 * G28.h
 *
 *  Created on: Sep 1, 2020
 *      Author: MStefan99
 */

#ifndef GPARSER_G28_H_
#define GPARSER_G28_H_


#include <cstdio>
#include <cstring>

#include "platform.h"
#include "GCode.h"


class G28 : public GCode {
public:
	G28();
	~G28() = default;

	G28* clone() const override;
	void execute() const override;

	const char* getType() const override;
};


#endif /* GPARSER_G28_H_ */
