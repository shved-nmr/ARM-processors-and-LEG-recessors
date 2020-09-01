/*
 * platform.h
 *
 *  Created on: 1 Sep 2020
 *      Author: MStefan99
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_


typedef struct {
	bool limitXLow;
	bool limitXHigh;
	bool limitYLow;
	bool limitYHigh;
} LimitSwitches_t;


#define DIRECTION_CLOCKWISE 0
#define DIRECTION_COUNTERCLOCKWISE 1

#define X_LENGTH 310
#define Y_LENGTH 380
#define X_DIRECTION DIRECTION_CLOCKWISE
#define Y_DIRECTION DIRECTION_CLOCKWISE

#define PLOTTING_SPEED 80
#define PEN_UP 160
#define PEN_DOWN 90


LimitSwitches_t getLimitSwitches();


#endif /* PLATFORM_H_ */
