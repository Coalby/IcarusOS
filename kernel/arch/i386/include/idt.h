#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_MAXSIZE         256
#define EXCEPTION_SIZE      32

//  Describes IDT entry. Refer to Section 2.4.3: IDTR Interrupt Descriptor Table Register 
//  of Intel Software Developer Manual, Volume 3-A
typedef struct {
    uint16_t offset_1;
	uint16_t segment_selector;
	uint8_t reserved;
	uint8_t attributes;
	uint16_t offset_2;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t    limit;
    uint32_t    base;
} __attribute__((packed)) idt_reg;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[IDT_MAXSIZE];
static idt_reg idtr;

void set_idt_descriptor(uint8_t vector, uint32_t offset, uint8_t attributes);
void set_idtr(idt_reg idtr);
void init_idt();

#endif