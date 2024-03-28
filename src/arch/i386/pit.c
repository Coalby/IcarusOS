#include "pit.h"
#include "system.h"
#include <kernel.h>

uint64_t global_ticks = 0;

void timer_install(uint16_t hertz) {
    uint16_t divisor = 1193180 / hertz;     // Short reason that its 11913180, its cheap ; Long reason, https://wiki.osdev.org/PIT#The_Oscillator
    
    uint8_t l = (uint8_t) (divisor & 0xFF);
    uint8_t h = (uint8_t) (divisor >> 8);
    
    outportb(PIT_COMMAND, 0x36);
    outportb(PIT_DATA0, l);                 // Low byte of divisor
    outportb(PIT_DATA0, h);                 // High byte of divisor
    registerIRQhandler(0, timer_handler);   // Sets up the system clock by installing the timer handler into IRQ0
}

void timer_handler(interruptFrame *frame) {
    global_ticks++;

    // Print every 18 clocks (approximately 1 second)
    // if (global_ticks % 18 == 0)
    // {
    //     terminal_setcolor(global_ticks % 15);
    //     terminal_writestring("PIT has been called! ");
    // }
}