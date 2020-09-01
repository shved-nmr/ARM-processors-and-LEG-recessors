/*
 * platform.cpp
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */


#include "platform.h"


LimitSwitches_t getLimitSwitches() {
	return LimitSwitches_t {true, true, true, true};
}
