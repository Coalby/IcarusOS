#include "idt.h"
#include <utils.h>
#include <kernel.h>

__attribute__((aligned(0x10))) 
static idt_entry_t idt[IDT_MAXSIZE];
static idt_reg idtr;

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
    __asm__ ("lidt %0" : : "m" (idtr));
    __asm__ ("sti");
} 

// TODO: Finish init_idt(); Need to implement idt stub
void init_idt()
{
    idtr.limit = 0xFFF;
    idtr.base  = (uintptr_t)&idt[0];

    for (uint16_t vector = 0; vector < 48; vector++) {
        set_idt_descriptor(vector, idt_stub_table[vector], INT_GATE_ATTRIBUTE);
    }

    // for (uint8_t vector = EXCEPTION_SIZE; vector < (IDT_MAXSIZE - 1); vector++) {
    //     set_idt_descriptor(vector, stub_table[i],TASK_GATE_ATTRIBUTE);
    // }

    set_idtr(idtr);
}
