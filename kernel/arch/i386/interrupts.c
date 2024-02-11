#include "interrupts.h"
#include <kernel.h>

void default_exception_handler(interruptFrame *frame) {
    disable_interrupts();
    terminal_writestring("EXCEPTION - ERROR CODE\n");
}

void default_interrupt_handler() {
    terminal_writestring("DEFAULT INTERRUPT\n");
}