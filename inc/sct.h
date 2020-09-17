/*
 * sct.h
 *
 *  Created on: Sep 14, 2020
 *      Author: MStefan99
 */

#ifndef SCT_H_
#define SCT_H_

#include <cstdint>


void sct_init();  // Call this before any other function
void stepper_move(unsigned int pps, unsigned int stepCountX, unsigned int stepCountY);  // Call this function to move given number of steps



#endif /* SCT_H_ */
