/*
 * M10.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef M10_H_
#define M10_H_

#include <cstdio>

#include "platform.h"
#include "GCode.h"


class M10 : public GCode {
public:
	M10();
	~M10();

	const char* getType() const override;

protected:

};


#endif /* M10_H_ */
