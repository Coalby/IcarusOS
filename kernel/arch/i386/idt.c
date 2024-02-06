#include "idt.h"
#include <kernel.h>

void set_idt_descriptor(uint8_t vector, void *isr, uint8_t attributes)
{
    idt_entry_t *entry = &idt[vector];

    entry->offset_1         = (uint16_t) ((uint32_t) isr & 0xFFFF);
    entry->segment_selector = 0x08;     // Kernel Mode Code Segment
    entry->reserved         = 0;
    entry->attributes       = attributes;
    entry->offset_2         = (uint16_t) ((uint32_t) isr >> 16);
}

void set_idtr(idt_reg idtr) {
    __asm__ __volatile__ (
        "lidt %0;"
        : : "m" (idtr)
    );
} 

// TODO: Finish init_idt(); Need to implement idt stub
void init_idt()
{
    for (uint8_t vector; vector < (EXCEPTION_SIZE - 1); vector++) {
        set_idt_descriptor(vector, ,0x8E);
    }

    idt_reg idtr;
    idtr.limit = 0xFFF;
}

