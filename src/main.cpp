/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "FreeRTOS.h"
#include "task.h"
#include "heap_lock_monitor.h"
#include "ITM_write.h"

#include "GParser/GLine.h"


/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	ITM_init();

	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
}


static void vTask1(void *pvParameters) {
	char inputString[80] {};
	Board_LED_Set(1, true);

	int i {0};
	int c;

	while (1) {
		while ((c = Board_UARTGetChar()) != -1) {
			inputString[i] = c;
			++i;
			if (c == '\r' || c == '\n') {
				GLine gcode {inputString};
				printf("%s", gcode.getCode()->getReply());
				i = 0;
			}
		}
	}
}


/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statistics collection */


int main(void)
{
	heap_monitor_setup();
	prvSetupHardware();

	xTaskCreate(vTask1, "Task 1",
				configMINIMAL_STACK_SIZE + 512, NULL, (tskIDLE_PRIORITY + 1UL),
				(TaskHandle_t *) NULL);

	vTaskStartScheduler();
	return 1;
}

