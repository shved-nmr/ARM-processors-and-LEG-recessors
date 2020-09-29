/*
 * stepper.h
 *
 *  Created on: Sep 14, 2020
 *      Author: MStefan99
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <cstdint>

#include "board.h"
#include "chip.h"

#include "config.h"
#include "plotter.h"


#define SAFE_PPS 500


void stepper_reenablePins();  // Call this to re-enable GPIO for stepper pins
void stepper_move(unsigned int pps, unsigned int stepCountX, unsigned int stepCountY);  // Call this function to move given number of steps
// This will disable GPIO function for stepper pins


#endif /* STEPPER_H_ */
