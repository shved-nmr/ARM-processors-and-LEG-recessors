#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif


#define CACHE_SIZE 20
#define READ_TIMEOUT 5000


#include <cr_section_macros.h>
#include <list>

#include "FreeRTOS.h"
#include "task.h"
#include "heap_lock_monitor.h"
#include "ITM_write.h"
#include "LpcUart.h"

#include "GParser/GLine.h"
#include "platform.h"


LpcUart* dbgu;


GLine readCommand();


void startup() {
	for (int i {0}; i < 3; ++i) {
		Board_LED_Set(1, true);
		vTaskDelay(250);
		Board_LED_Set(1, false);
		vTaskDelay(250);
	}
}


/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	ITM_init();
	LpcPinMap none = {-1, -1}; // unused pin has negative values in it
	LpcPinMap txpin = { 0, 18 }; // transmit pin that goes to debugger's UART->USB converter
	LpcPinMap rxpin = { 0, 13 }; // receive pin that goes to debugger's UART->USB converter
	LpcUartConfig cfg = {
			LPC_USART0,
			115200,
			UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1,
			false,
			txpin,
			rxpin,
			none,
			none
	};
	dbgu = new LpcUart(cfg);


	setLaserPower(0);
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
}


GLine readCommand() {
	char inputString[80] {};
	int i {0};
	char c;
	auto startTime = xTaskGetTickCount();

	while (1) {
		if (dbgu->read(c)) {
			Board_LED_Set(1, true);
			inputString[i] = c;
			++i;

			if (c == '\r' || c == '\n') {
				Board_LED_Set(1, false);
				return GLine {inputString};
			}
		} else if (xTaskGetTickCount() - startTime > READ_TIMEOUT) {
			throw -1;  // Read timeout exceeded
		}
	}
}


static void vTask1(void *pvParameters) {
	std::list<GLine> lineList;
	bool failed {true};

	printf("Plotter started\r\n");
	#ifdef DRY_RUN
		printf("Dry run mode enabled\r\n");
	#else
		printf("Warning: Dry run mode disabled!\r\n");
	#endif
	startup();
	printf("Ready to plot!\r\n");

	while (1) {
		do {
			try {  // Successfully read command
				GLine line {readCommand()};
				auto type = line.getCode()->getType();
				if (strstr(type, "M10") || strstr(type, "M11")) {  // Not caching status commands
					break;
				} else {  // Caching command
					lineList.push_back(line);
					printf("%s", line.getCode()->getReply());
				}
				failed = false;
			} catch (int statusCode) {  // Failed to read command
				if (!failed) {
					printf("Failed to read command\r\nIs plotting done?\r\n");
					Board_LED_Set(1, false);
					Board_LED_Set(2, false);
					Board_LED_Set(0, true);
				}
				failed = true;
			}
		} while (lineList.size() < CACHE_SIZE);

		for (const auto line: lineList) {  // Executing cached commands
			line.getCode()->execute();  // This should be a blocking call
			vTaskDelay(10);  // Delay simulating extruder movement
		}
		lineList.clear();  // Clearing cache
		ITM_write("Cache exhausted, refilling...\r\n");
	}
}


// the following is required if runtime statistics are to be collected
extern "C" {
void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}
}


int main(void) {
	heap_monitor_setup();
	prvSetupHardware();

	xTaskCreate(vTask1, "Task 1",
				configMINIMAL_STACK_SIZE + 512, NULL, (tskIDLE_PRIORITY + 1UL),
				(TaskHandle_t *) NULL);

	vTaskStartScheduler();
	return 1;
}

