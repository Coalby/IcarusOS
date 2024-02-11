#pragma once

#include <stdint.h>

typedef struct
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;

    uint32_t eip, cs, eflags, usermode_esp, usermode_ss;
} interruptFrame;

void default_exception_handler(interruptFrame *frame);
void default_interrupt_handler();
