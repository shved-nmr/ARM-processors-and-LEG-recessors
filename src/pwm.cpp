/*
 * pwm.cpp
 *
 *  Created on: Sep 26, 2020
 *      Author: MStefan99
 */


#include "pwm.h"


#define SYSAHBCLKCTRL1 ( *(uint32_t*) ( 0x400740C8 ) )
#define PRESETCTRL1 ( *(uint32_t*) ( 0x40074048 ) )
#define PINASSIGN7 ( *(uint32_t*) ( 0x4003801C ) )
#define PINASSIGN8 ( *(uint32_t*) ( 0x40038020 ) )
#define ISER0 ( *(uint32_t*) ( 0xE000E100 ) )


#define getTimer(channel) (\
	(channel < 3? (LPC_SCT0) : (LPC_SCT1))\
)


#define getAssignRegister(channel) (\
	(channel < 3? (PINASSIGN7) : (PINASSIGN8))\
)


#define getOffset(channel) (\
	(channel < 3? channel * 8 + 8 : (channel % 3) * 8)\
)


#define getEvent(channel) (\
	(channel % 3 + 1)\
)



static void timer_init(LPC_SCT_T* timer) {
	timer->CTRL_L |= (1 << 2);  // halt timer before configuring

	timer->CONFIG |= 1 | (1 << 17);  // unified timer, auto limit

	timer->MATCHREL[0].U = 0;  // setting match 0 to 0
	timer->MATCHREL[1].U =
	timer->MATCHREL[2].U =
	timer->MATCHREL[3].U = 0;  // setting match 1, 2 and 3 to 0

	timer->EVENT[0].STATE =
	timer->EVENT[1].STATE =
	timer->EVENT[2].STATE =
	timer->EVENT[3].STATE = ~0;  // events 0, 1, 2 and 3 happen in all states

	timer->EVENT[0].CTRL = (0 << 0) |  // event 0 related to match 0
		(1 << 12);  // COMBMODE[13:12] = match condition only
	timer->EVENT[1].CTRL = (1 << 0) |  // event 1 related to match 1
		(1 << 12);  // COMBMODE[13:12] = match condition only
	timer->EVENT[2].CTRL = (2 << 0) |  // event 2 related to match 2
		(1 << 12);  // COMBMODE[13:12] = match condition only
	timer->EVENT[3].CTRL = (3 << 0) |  // event 3 related to match 3
		(1 << 12);  // COMBMODE[13:12] = match condition only

	timer->OUT[0].SET =
	timer->OUT[1].SET =
	timer->OUT[2].SET = (1 << 0);  // event 0 will set SCT_OUT0, 1 and 2
	timer->OUT[0].CLR = (1 << 1);  // event 1 will clear SCT_OUT0
	timer->OUT[1].CLR = (1 << 2);  // event 2 will clear SCT_OUT1
	timer->OUT[2].CLR = (1 << 3);  // event 3 will clear SCT_OUT2

	timer->COUNT_U = 0;  // reset counter to 0
	timer->CTRL_L &= ~(1 << 2);  // unhalt timer
}


void pwm_enable(uint8_t channel, uint8_t port, uint8_t pin) {
	SYSAHBCLKCTRL1 |= 1u << 2 | 1u << 3;  // enable clock to SCT 0 and 1
	PRESETCTRL1 &= ~(1u << 2 | 1u << 3);  // clear SCT reset

	getAssignRegister(channel) &= (~(0xff << getOffset(channel))
			| ((port << 5 | pin) << getOffset(channel)));

	timer_init(getTimer(channel));
}


void pwm_disable(uint8_t channel) {
	getAssignRegister(channel) |= (0xff << getOffset(channel));
}


void pwm_setFreq(uint8_t channel, uint32_t freq) {
	uint32_t period = SystemCoreClock / freq;

	getTimer(channel)->MATCHREL[0].U = period? period: 1;
	getTimer(channel)->CTRL_L |= 1 << 3;  // reset count to 0
	pwm_setDuty(channel, 0);
}


void pwm_setDuty(uint8_t channel, uint8_t duty) {
	uint32_t period {getTimer(channel)->MATCHREL[0].U};

	getTimer(channel)->MATCHREL[getEvent(channel)].U
		= (float) period * duty / 0xff;
}

