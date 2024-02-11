#include "handlers.h"
#include <kernel.h>

void default_exception_handler() {
    disable_interrupts();
    terminal_writestring("Unhandled Exception\n");
}

void default_interrupt_handler() {
    terminal_writestring("Unhandled Interrupt\n");
}