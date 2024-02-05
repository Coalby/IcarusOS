#include "idt.h"
#include <kernel.h>

void set_idt_descriptor(uint8_t vector, uint32_t offset, uint8_t attributes)
{
    idt_entry_t *entry = &idt[vector];

    entry->offset_1         = (uint16_t) (offset & 0xFFFF);
    entry->segment_selector = 0x08;     // Kernel Mode Code Segment
    entry->reserved         = 0;
    entry->attributes       = attributes;
    entry->offset_2         = (uint16_t) (offset >> 16);
}

// TODO: Finish init_idt(); Need to implement idt stub
void init_idt()
{
    for (uint8_t vector; vector < (EXCEPTION_SIZE - 1); vector++) {
        set_idt_descriptor(vector, ,0x8E);
    }

    for (uint8_t vector = EXCEPTION_SIZE; vector < (IDT_MAXSIZE - 1); vector++) {
        set_idt_descriptor(vector, );
    }
}

