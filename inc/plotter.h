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


void plotter_init();  // Call this function before any other function
void plotter_setDim(uint32_t sizeX, uint32_t sizeY);
void plotter_moveTo(float x, float y, uint32_t pps);
void plotter_calibrate();
void plotter_home();


#endif /* PLOTTER_H_ */
