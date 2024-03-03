// Contains Interrupt Handler Implementation
#pragma once

#include <stdint.h>

// PIC (Programmable Interrupt Controller) definitions
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

typedef void (*handler)(interruptFrame *regs);

void remap_pic();
void registerIRQhandler(uint8_t id, handler handler);

void interrupt_handler(interruptFrame *frame);

