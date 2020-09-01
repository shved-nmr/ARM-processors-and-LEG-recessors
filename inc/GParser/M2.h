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

protected:

};


#endif /* M2_H_ */
