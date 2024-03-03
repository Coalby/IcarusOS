// PIT (Programmable Interval Timer) Implementation
#pragma once

#include "stdint.h"
#include "handlers.h"

// PIT_DATA1 is unusable and may not even exist ; Outdated
#define PIT_DATA0       0x40        // Connected to IRQ0 in the PIC ; IRQ0 is generated on RISING edge ; Read/Write
#define PIT_DATA2       0x42        // Connected to PC speaker ; Read/Write
#define PIT_COMMAND     0x43        // Controls usage of PIT ; Write only

void timer_handler(interruptFrame *frame);
void timer_install(uint16_t hertz);