#include "idt.h"
#include "handlers.h"
#include <system.h>
#include <kernel.h>

__attribute__((aligned(0x10))) 
static idt_entry_t idt[IDT_MAXSIZE];
static idt_reg idtr;

void set_idt_descriptor(uint8_t vector, void *isr, uint8_t attributes)
{
    idt_entry_t *entry = &idt[vector];

    entry->offset_1         = (uint16_t) ((uint32_t)isr & 0xFFFF);
    entry->segment_selector = 0x08;     // Kernel Mode Code Segment
    entry->reserved         = 0;
    entry->attributes       = attributes;
    entry->offset_2         = (uint16_t) ((uint32_t)isr >> 16);
}

void set_idtr(idt_reg idtr) {
    __asm__ ("lidt %0" : : "m" (idtr));
} 

void init_idt()
{
    idtr.limit = (uint16_t) (IDT_MAXSIZE * sizeof(idt_entry_t)) - 1;
    idtr.base  = (uint32_t)&idt;
    
    remap_pic();

    for (uint16_t vector = 0; vector < 256; vector++) {
        set_idt_descriptor(vector, idt_stub_table[vector], INT_GATE_ATTRIBUTE);
    }

    set_idtr(idtr);
}