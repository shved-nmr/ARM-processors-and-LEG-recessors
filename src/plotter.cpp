/*
 * plotter.cpp
 *
 *  Created on: Sep 18, 2020
 *      Author: MStefan99
 */


#include "plotter.h"


#define PINASSIGN7 ( *(uint32_t*) ( 0x4003801C ) )
#define PINASSIGN8 ( *(uint32_t*) ( 0x40038020 ) )


static uint32_t stepsX {0};
static uint32_t stepsY {0};
static uint32_t sizeX {0};
static uint32_t sizeY {0};
static uint32_t currentStepsX {0};
static uint32_t currentStepsY {0};
static bool directionX {true};
static bool directionY {true};

static bool initialized {false};

static DigitalIoPin* limXLow;
static DigitalIoPin* limXHigh;
static DigitalIoPin* limYLow;
static DigitalIoPin* limYHigh;
static DigitalIoPin* dirX;
static DigitalIoPin* stepX;
static DigitalIoPin* dirY;
static DigitalIoPin* stepY;


static void init() {
	limXLow = new DigitalIoPin {0, 29, DigitalIoPin::pinMode::pullup, true};
	limXHigh = new DigitalIoPin {0, 9, DigitalIoPin::pinMode::pullup, true};
	limYLow = new DigitalIoPin {1, 3, DigitalIoPin::pinMode::pullup, true};
	limYHigh = new DigitalIoPin {0, 0, DigitalIoPin::pinMode::pullup, true};

	dirX = new DigitalIoPin {1, 0, DigitalIoPin::pinMode::output};
	stepX = new DigitalIoPin {0, 24, DigitalIoPin::pinMode::output};
	dirY = new DigitalIoPin {0, 28, DigitalIoPin::pinMode::output};
	stepY = new DigitalIoPin {0, 27, DigitalIoPin::pinMode::output};

	initialized = true;
}


void plotter_calibrate() {
	if (!initialized) {
		init();
	}
	stepper_reenablePins();

	while (*limXHigh || *limXLow || *limYLow || *limYHigh);

	// Calibrating x-axis
	do {
		*dirX = directionX;
		*stepX = true;
		vTaskDelay(1);
		*stepX = false;
		vTaskDelay(1);
	} while (!*limXLow && !*limXHigh);

	do {
		*dirX = !directionX;
		++stepsX;
		*stepX = true;
		vTaskDelay(1);
		*stepX = false;
		vTaskDelay(1);
	} while (!*limXLow && !*limXHigh);

	// Calibrating y-axis
	do {
		*dirY = directionY;
		*stepY = true;
		vTaskDelay(1);
		*stepY = false;
		vTaskDelay(1);
	} while (!*limYLow && !*limYHigh);

	do {
		*dirY = !directionY;
		++stepsY;
		*stepY = true;
		vTaskDelay(1);
		*stepY = false;
		vTaskDelay(1);
	} while (!*limYLow && !*limYHigh);
}


void plotter_setDim(uint32_t x, uint32_t y) {
	sizeX = x;
	sizeY = y;
}


void plotter_setDir(bool dirX, bool dirY) {
	directionX = dirX;
	directionY = dirY;
}


void plotter_moveTo(float x, float y, uint32_t pps) {
	if (!initialized) {
		init();
	}

	if (!stepsX || !stepsY || !sizeX || !sizeY) {
		return;
	}

	uint32_t targetStepsX = x / (float)sizeX * (float)stepsX;
	uint32_t targetStepsY = y / (float)sizeY * (float)stepsY;

	int dx = targetStepsX - currentStepsX;
	int dy = targetStepsY - currentStepsY;

	if (dx < 0) {
		dx = -dx;
		*dirX = !directionX;
	} else {
		*dirX = directionX;
	}
	if (dy < 0) {
		*dirY = !directionY;
		dy = -dy;
	} else {
		*dirY = directionY;
	}

	stepper_move(pps, dx, dy);
	currentStepsX = targetStepsX;
	currentStepsY = targetStepsY;
}


void plotter_home() {
	if (!initialized) {
		init();
	}
	stepper_reenablePins();

	do {
		*dirX = !directionX;
		++stepsX;
		*stepX = true;
		vTaskDelay(1);
		*stepX = false;
		vTaskDelay(1);
	} while (!*limXLow && !*limXHigh);

	do {
		*dirY = !directionY;
		++stepsY;
		*stepY = true;
		vTaskDelay(1);
		*stepY = false;
		vTaskDelay(1);
	} while (!*limYLow && !*limYHigh);

	currentStepsX = currentStepsY = 0;
}

