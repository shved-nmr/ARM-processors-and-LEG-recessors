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

static DigitalIoPin* lim1 {nullptr};
static DigitalIoPin* lim2 {nullptr};
static DigitalIoPin* lim3 {nullptr};
static DigitalIoPin* lim4 {nullptr};

DigitalIoPin* limXLow {nullptr};
DigitalIoPin* limXHigh {nullptr};
DigitalIoPin* limYLow {nullptr};
DigitalIoPin* limYHigh {nullptr};

static DigitalIoPin* dirX {nullptr};
static DigitalIoPin* dirY {nullptr};
static DigitalIoPin* stepX {nullptr};
static DigitalIoPin* stepY {nullptr};


static void init() {
	lim1 = new DigitalIoPin {0, 29, DigitalIoPin::pinMode::pullup, true};
	lim2 = new DigitalIoPin {0, 9, DigitalIoPin::pinMode::pullup, true};
	lim3 = new DigitalIoPin {1, 3, DigitalIoPin::pinMode::pullup, true};
	lim4 = new DigitalIoPin {0, 0, DigitalIoPin::pinMode::pullup, true};

	dirX = new DigitalIoPin {1, 0, DigitalIoPin::pinMode::output};
	stepX = new DigitalIoPin {0, 24, DigitalIoPin::pinMode::output};
	dirY = new DigitalIoPin {0, 28, DigitalIoPin::pinMode::output};
	stepY = new DigitalIoPin {0, 27, DigitalIoPin::pinMode::output};

	initialized = true;
}


static bool limitClosed() {
	return *lim1 || *lim2 || *lim3 || *lim4;
}


static DigitalIoPin* getClosedLimit() {
	if (*lim1) {
		return lim1;
	} else if (*lim2) {
		return lim2;
	} else if (*lim3) {
		return lim3;
	} else if (*lim4) {
		return lim4;
	} else {
		return nullptr;
	}
}


static void step(DigitalIoPin& pin) {
	pin = true;
	vTaskDelay(1);
	pin = false;
	vTaskDelay(1);
}


LimitSwitches_t plotter_getLimits() {
	return {*limYLow, *limYHigh,
		*limXLow, *limXHigh};
}


bool plotter_checkLimit() {
	return ((*dirX? *limXHigh : *limXLow)
			|| (*dirY? *limYHigh : *limYLow));
}


void plotter_calibrate() {
	if (!initialized) {
		init();
	}
	stepper_reenablePins();
	stepsX = stepsY = 0;

	while (limitClosed());  // wait for all switches to be released

	// Calibrating x-axis
	do {  // finding high x limit
		*dirX = directionX;
		step(*stepX);
	} while (!limitClosed());
	limXHigh = getClosedLimit();

	do {  // finding low x limit
		*dirX = !directionX;
		++stepsX;
		step(*stepX);
	} while (!limitClosed());
	limXLow = getClosedLimit();

	do {  // opening y limit
		*dirX = directionX;
		step(*stepX);
	} while (limitClosed());

	// Calibrating y-axis
	do {  // finding high y limit
		*dirY = directionY;
		step(*stepY);
	} while (!limitClosed());
	limYHigh = getClosedLimit();

	do {  // finding low y limit
		*dirY = !directionY;
		++stepsY;
		step(*stepY);
	} while (!limitClosed());
	limYLow = getClosedLimit();

	do {  // opening x limit
		*dirY = directionY;
		step(*stepY);
	} while (limitClosed());
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

	do {  // moving x home
		*dirX = !directionX;
		step(*stepX);
	} while (!*limXLow);

	do {  // opening x limit
		*dirX = directionX;
		step(*stepX);
	} while (*limXLow);

	do {  // moving y home
		*dirY = !directionY;
		step(*stepY);
	} while (!*limYLow);

	do {  // opening y limit
		*dirY = directionY;
		step(*stepY);
	} while (*limYLow);

	currentStepsX = currentStepsY = 0;
}

