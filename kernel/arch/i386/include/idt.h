#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_MAXSIZE         256
#define EXCEPTION_SIZE      32

//  Describes IDT entry. Refer to Section 2.4.3: IDTR Interrupt Descriptor Table Register 
//  of Intel Software Developer Manual, Volume 3-A
typedef struct {
    uint16_t    isr_low;
    uint16_t    kernel_cs;
	uint8_t	    ist; 
	uint8_t     attributes;
	uint16_t    isr_mid;
	uint32_t    isr_high;
	uint32_t    reserved;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t    limit;
    uint32_t    base;
} __attribute__((packed)) idt_ptr;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[IDT_MAXSIZE];

static idt_ptr idtr;

#endif