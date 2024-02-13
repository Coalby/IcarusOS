#pragma once

#include <stdint.h>

// PIC definitions
#define MASTER_PIC_COMMAND  0x20
#define SLAVE_PIC_COMMAND   0xA0
#define MASTER_PIC_DATA     0x21
#define SLAVE_PIC_DATA      0xA1

#define PIC_INIT            0x11

#define MASTER_PIC_OFFSET   0x20
#define SLAVE_PIC_OFFSET    0x28

#define PIC_8086_MODE       0x01

#define DEFAULT_MASTER_MASK 0x00
#define DEFAULT_SLAVE_MASK  0x00

typedef struct
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;

    uint32_t eip, cs, eflags, usermode_esp, usermode_ss;
} interruptFrame;

void default_exception_handler(interruptFrame *frame);
void default_interrupt_handler();

// TODO: Replace other handlers with interrupt_handler(interruptFrame *frame)
void interrupt_handler(interruptFrame *frame);
