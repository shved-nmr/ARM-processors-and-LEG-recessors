#include "stepper.h"
#include "DigitalIoPin.h"
#include "FreeRTOS.h"
#include "task.h"

#ifndef USE_SCT

void pin_toggle(DigitalIoPin pinToToggle, unsigned int pps) {
	pinToToggle.write(true);
	vTaskDelay(500 / pps);
	pinToToggle.write(false);
	vTaskDelay(500 / pps);
}


void stepper_init() {
	//Nothing to do
}


void stepper_move(unsigned int pps, unsigned int x2, unsigned int y2) {
	DigitalIoPin stepX(0, 27, DigitalIoPin::pinMode::output);
	DigitalIoPin stepY(0, 24, DigitalIoPin::pinMode::output);
    bool isSteep = true;
    unsigned int x1 = 0;
    unsigned int y1 = 0;

    if (x2-x1 >= y2-y1) {
        isSteep = false;
    } else {
        isSteep = true;
    }

    if (!isSteep) {
        int m_slope = 2 * (y2 - y1);
        int slope_error = m_slope - (x2 - x1);

        for (unsigned int x = x1, y = y1; x <= x2; x++) {
            slope_error += m_slope;

            if (slope_error >= 0) {
                y++;
                pin_toggle(stepY, pps);
                slope_error -= 2 * (x2 - x1);
            }
            pin_toggle(stepX, pps);
        }
    } else {
        int m_slope = 2 * (x2-x1);
        int slope_error = m_slope - (y2-y1);

        for (unsigned int y = y1, x = x1; y <= y2; y++) {
            slope_error += m_slope;

            if (slope_error >= 0) {
                x++;
                pin_toggle(stepX, pps);
                slope_error  -= 2 * (y2 - y1);
            }
            pin_toggle(stepY, pps);
        }
    }
}

#endif
