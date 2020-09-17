/*
 * sct.cpp
 *
 *  Created on: Sep 14, 2020
 *      Author: MStefan99
 */


#include "sct.h"
#include "board.h"
#include "chip.h"


#define SYSAHBCLKCTRL1 ( *(uint32_t*) ( 0x400740C8 ) )
#define PRESETCTRL1 ( *(uint32_t*) ( 0x40074048 ) )
#define PINASSIGN7 ( *(uint32_t*) ( 0x4003801C ) )
#define PINASSIGN8 ( *(uint32_t*) ( 0x40038020 ) )
#define ISER0 ( *(uint32_t*) ( 0xE000E100 ) )


static uint32_t totalXSteps;
static uint32_t totalYSteps;
static uint32_t currentXSteps;
static uint32_t currentYSteps;


extern "C" {
void SCT0_IRQHandler() {
	++currentXSteps;

	LPC_SCT0->EVFLAG &= ~(1 << 2);  // clear interrupt flag
	if (currentXSteps >= totalXSteps) {
		LPC_SCT0->CTRL_L |= 1 << 2;  // halt SCT0
	}
}
}


extern "C" {
void SCT1_IRQHandler() {
	++currentYSteps;

	LPC_SCT1->EVFLAG &= ~(1 << 2);  // clear interrupt flag
	if (currentYSteps >= totalYSteps) {
		LPC_SCT1->CTRL_L |= 1 << 2;  // halt SCT1
	}
}
}


void timer_init(LPC_SCT_T* timer) {
	timer->CONFIG |= 1;  // unified timer

	timer->EVENT[0].STATE = (1 << 0);   // event 0 only happens in state 0
	timer->EVENT[0].CTRL = (0 << 0) |  // related to match 0
		(1 << 12) |  // COMBMODE[13:12] = match condition only
		(1 << 14) |  // STATELD[14] = STATEV is loaded into state
		(1 << 15);  // STATEV[15] = 1 (new state is 1)
	timer->EVENT[1].STATE = (1 << 1);  // event 1 only happens in state 1
	timer->EVENT[1].CTRL = (0 << 0) |  // related to match 0
		(1 << 12) |  // COMBMODE[13:12] = match condition only
		(1 << 14) |  // STATELD[14] = STATEV is loaded into state
		(0 << 15);  // STATEV[15] = 0 (new state is 0)
	timer->EVEN = 0x2;  // Enabling interrupt for event 1

	timer->OUT[0].SET = (1 << 0);  // event 0 will set SCT_OUT0
	timer->OUT[0].CLR = (1 << 1);  // event 1 will clear SCT_OUT0

	timer->LIMIT_L = 0x3;  // events 0 and 1 are used as counter limit
}


void timer_start(LPC_SCT_T* timer, uint32_t prescaler) {
	timer->MATCHREL[0].U = prescaler;  // setting prescaler
	timer->COUNT_U = 0;
	timer->CTRL_L &= ~(1 << 2);  // unhalt by clearing bit 2 of CTRL register
}


void sct_init() {
	SYSAHBCLKCTRL1 |= 1u << 2 | 1u << 3;  // enable power to SCT 0 and 1

	PRESETCTRL1 &= ~(1u << 2 | 1u << 3);  // clear SCT reset statuses

	PINASSIGN7 = (~(0xff << 8) | 24u << 8);  // enable SCT 0 output on pin 0_24
	PINASSIGN8 = (~(0xff) | 27u);  // enable SCT 1 output on pin 0_27
	ISER0 |= 1u << 16 | 1u << 17;  // enable interrupts in the NVIC

	timer_init(LPC_SCT0);
	timer_init(LPC_SCT1);
}


void stepper_move(unsigned int pps, unsigned int stepCountX, unsigned int stepCountY) {
	uint32_t prescaler = (SystemCoreClock / pps / 2) - 1;

	totalXSteps = stepCountX;
	totalYSteps = stepCountY;
	currentXSteps = currentYSteps = 0;

	timer_start(LPC_SCT0, prescaler);
	timer_start(LPC_SCT1, prescaler);

	while (!(LPC_SCT0->CTRL_L & (1 << 2)) || !(LPC_SCT1->CTRL_L & (1 << 2)));  // Blocking until movement is complete
}



