/*
 * M10.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef M10_H_
#define M10_H_

#include <cstdio>
#include <cstring>

#include "platform.h"
#include "GCode.h"


class M10 : public GCode {
public:
	M10();
	~M10();

	M10* clone() const override;
	void execute() const override;

	const GCode::CodeType getType() const override;
};


#endif /* M10_H_ */
