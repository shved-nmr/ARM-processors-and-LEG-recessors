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
#define CONF ( *(uint32_t*) ( 0x1C018000 ) )
#define COUNT_L ( *(uint16_t*) ( 0x1C018040 ) )
#define COUNT_H ( *(uint16_t*) ( 0x1C018042 ) )
#define MATCH_L(x) ( *(uint16_t*) ( 0x1C018100 + 2 * x ) )
#define MATCH_H(x) ( *(uint16_t*) ( 0x1C018110 + 2 * x ) )
#define EV_CTRL_L(x) ( *(uint32_t*) ( 0x1C018304 + 4 * x ) )
#define EV_CTRL_H(x) ( *(uint32_t*) ( 0x1C01C304 + 4 * x ) )
#define EV_STATE_L(x) ( *(uint32_t*) ( 0x1C018300 + 4 * x) )
#define EV_STATE_H(x) ( *(uint32_t*) ( 0x1C01C300 + 4 * x ) )
#define OUT_SET_L(x) ( *(uint32_t*) ( 0x1C018500 + 4 * x ) )
#define OUT_CLR_L(x) ( *(uint32_t*) ( 0x1C018504 + 4 * x ) )
#define EVEN ( *(uint32_t*) ( 0x1C0180F0 ) )
#define EVFLAG ( *(uint32_t*) ( 0x1C0180F4 ) )
#define CTR ( *(uint32_t*) ( 0x1C018004 ) )
#define ISER0 ( *(uint32_t*) ( 0xE000E100 ) )


extern "C" {
void SCT0_IRQHandler() {
	Board_LED_Set(0, true);
}
}

extern "C" {
void SCT1_IRQHandler() {
	Board_LED_Set(1, true);
}
}


void sct_init() {
	SYSAHBCLKCTRL1 |= 1u << 2 | 1u << 3;  // Enable power to SCT 0 and 1

	PRESETCTRL1 &= ~(1u << 2 | 1u << 3);  // Clear SCT reset statuses

	PINASSIGN7 = (~(0xff << 8) | 24u << 8);  // Enable SCT 0 output on pin 0_24
	PINASSIGN8 = (~(0xff) | 27u);  // Enable SCT 1 output on pin 0_27

	// SCT setup
	CONF = 1u << 17;  // Setting up SCT as two timers
	COUNT_L = 0u;  // Setting counts to 0
	COUNT_H = 0u;

	EVEN |= 1u;  // Enabling interrupts for event 0

	// Setting up low interrupt
	MATCH_L(0) = 0xff;  // Setting match value
	EV_STATE_L(0) = ~0;  // Enabling event 0
	EV_CTRL_L(0) |= 1u << 12u;  // Configuring match event

	// Setting up high interrupt
	MATCH_H(0) = 0xff;
	EV_STATE_H(0) = ~0;
	EV_CTRL_H(0) |= 1u << 4u | 1u << 12u;

	// Configuring pin outputs
	OUT_SET_L(0) = 1;
	OUT_CLR_L(1) = 1u << 1;

	EVFLAG = 1u;  // Enabling interrupt
	ISER0 |= 1u << 16 | 1u << 17;  // Enabling interrupt in the NVIC
	CTR |= 0xff << 5 | 0xff << 21;  // Setting prescalers
	CTR &= ~(1u << 2u | 1u << 18u);  // Starting SCTs
}



