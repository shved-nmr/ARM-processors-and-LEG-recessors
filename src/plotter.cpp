/*
 * plotter.cpp
 *
 *  Created on: Sep 18, 2020
 *      Author: MStefan99
 */


#include "plotter.h"


#define PINASSIGN7 ( *(uint32_t*) ( 0x4003801C ) )
#define PINASSIGN8 ( *(uint32_t*) ( 0x40038020 ) )


static uint32_t sizeX;
static uint32_t sizeY;
static float currentX {0};
static float currentY {0};


void plotter_init() {

}


void plotter_calibrate() {
	DigitalIoPin limXLow {1, 3, DigitalIoPin::pinMode::pullup, true};
	DigitalIoPin limXHigh {0, 0, DigitalIoPin::pinMode::pullup, true};
	DigitalIoPin limYLow {0, 29, DigitalIoPin::pinMode::pullup, true};
	DigitalIoPin limYHigh {0, 9, DigitalIoPin::pinMode::pullup, true};

	DigitalIoPin dirX {0, 28, DigitalIoPin::pinMode::output};
	DigitalIoPin stepX {0, 27, DigitalIoPin::pinMode::output};
	DigitalIoPin dirY {1, 0, DigitalIoPin::pinMode::output};
	DigitalIoPin stepY {0, 24, DigitalIoPin::pinMode::output};

	PINASSIGN7 = PINASSIGN8 = ~0;

	while (limXHigh || limXLow || limYLow || limYHigh);

	// Calibrating x-axis
	while (!limXLow) {
		dirX = false;
		stepX = true;
		vTaskDelay(10);
		stepX = false;
		vTaskDelay(10);
	}

	while (!limXHigh) {
		dirX = true;
		++sizeX;
		stepX = true;
		vTaskDelay(10);
		stepX = false;
		vTaskDelay(10);
	}
	currentX = 0;

	// Calibrating y-axis
	while (!limYLow) {
		dirY = false;
		stepY = true;
		vTaskDelay(10);
		stepY = false;
		vTaskDelay(10);
	}

	while (!limYHigh) {
		dirY = true;
		++sizeY;
		stepY = true;
		vTaskDelay(10);
		stepY = false;
		vTaskDelay(10);
	}
	currentY = 0;
}

