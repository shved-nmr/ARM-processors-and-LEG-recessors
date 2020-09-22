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
#include "log.h"


char* readCommand();
LpcUart* uart;


void startup() {
	log("Startup sequence started\r\n");
	for (int i {0}; i < 3; ++i) {
		Board_LED_Set(1, true);
		vTaskDelay(250);
		Board_LED_Set(1, false);
		vTaskDelay(250);
	}
	platform_init();
	log("Startup sequence finished\r\n");
}


/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	ITM_init();

	setLaserPower(0);
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);

	uart = new LpcUart({
		LPC_USART0,
		115200,
		UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1,
		false,
		{0, 18},
		{0, 13},
		{-1, -1},
		{-1, -1}
	});

	log("Hardware setup done\r\n");
}


char* readCommand() {
	auto inputString = new char[80] {};
	int i {0};
	char c;
	auto startTime {xTaskGetTickCount()};

	while (1) {
		if (uart->read(c)) {
			Board_LED_Set(1, true);
			inputString[i] = c;
			++i;

			if (c == '\r' || c == '\n') {
				Board_LED_Set(1, false);
				return inputString;
			}
		} else if (xTaskGetTickCount() - startTime > READ_TIMEOUT || i > 79) {
			delete[] (inputString);
			return nullptr;
		}
	}
}


static void vTask1(void *pvParameters) {
	std::list<GLine> lineList;
	bool failed {true};
	char* command {nullptr};

	info("Plotter started\r\n");
	#ifdef DRY_RUN
		info("Dry run mode enabled\r\n");
	#else
		warn("Warning: Dry run mode disabled!\r\n");
	#endif
	startup();
	info("Ready to plot!\r\n");

	while (1) {
		do {
			command = readCommand();
			if (command) {  // Successfully read command
				GLine line {command};
				auto type = line.getCode()->getType();
				if (type == GCode::CodeType::M10 || type == GCode::CodeType::M11) {  // Not caching status commands
					break;
				} else {  // Caching command
					log("Command read\r\n");
					lineList.push_back(line);
					printf("%s", line.getCode()->getReply());
					delete[] (command);
					command = nullptr;
				}
				failed = false;
			} else {  // Command was not read due to an error
				if (!failed) {
					log("Failed to read command\r\nIs plotting done?\r\n");
					Board_LED_Set(1, false);
					Board_LED_Set(2, false);
					Board_LED_Set(0, true);
				}
				failed = true;
				break;
			}
		} while (lineList.size() < CACHE_SIZE);

		for (const auto line: lineList) {  // Executing cached commands
			log("Executing command...\r\n");
			line.getCode()->execute();  // This should be a blocking call
		}
		lineList.clear();  // Clearing cache
		log("Cache exhausted, refilling...\r\n");
		if (command) {
			GLine line {command};
			log("Executing status command\r\n");
			line.getCode()->execute();
			printf("%s", line.getCode()->getReply());
			delete[] (command);
			command = nullptr;
		}
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
	log("Starting kernel\r\n");

	xTaskCreate(vTask1, "Task 1",
				configMINIMAL_STACK_SIZE + 512, NULL, (tskIDLE_PRIORITY + 1UL),
				(TaskHandle_t *) NULL);

	vTaskStartScheduler();
	return 1;
}

