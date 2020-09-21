/*
 * M11.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef M11_H_
#define M11_H_

#include <cstdio>
#include <cstring>

#include "platform.h"
#include "GCode.h"


class M11 : public GCode {
public:
	M11();
	~M11();

	M11* clone() const override;
	void execute() const override;

	const GCode::CodeType getType() const override;
};


#endif /* M11_H_ */
