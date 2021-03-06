/*
 * plotter.h
 *
 *  Created on: Sep 18, 2020
 *      Author: MStefan99
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <cstdint>

#include "FreeRTOS.h"
#include "task.h"

#include "DigitalIoPin.h"
#include "stepper.h"


typedef struct {
	bool limitXLow;
	bool limitXHigh;
	bool limitYLow;
	bool limitYHigh;
} LimitSwitches_t;


void plotter_setDim(uint32_t sizeX, uint32_t sizeY);
void plotter_setDir(bool dirX, bool dirY);
void plotter_moveTo(float x, float y, uint32_t pps);
void plotter_calibrate();
void plotter_home();
LimitSwitches_t plotter_getLimits();

bool plotter_checkLimit();


#endif /* PLOTTER_H_ */
