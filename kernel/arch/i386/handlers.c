#include "handlers.h"
#include "system.h"
#include <utils.h>
#include <kernel.h>

char *exceptions[] = {"Division By Zero",
                      "Debug",
                      "Non Maskable Interrupt",
                      "Breakpoint",
                      "Overflow",
                      "Out of Bounds",
                      "Invalid Opcode",
                      "Device Not Available",

                      "Double Fault",
                      "Coprocessor Segment Overrun",
                      "Invalid TSS",
                      "Segment Not Present",
                      "Stack-Segment Fault",
                      "General Protection Fault",
                      "Page Fault",
                      "Unknown Interrupt",

                      "x87 Floating-Point Exception",
                      "Alignment Check",
                      "Machine Check",
                      "SIMD Floating-Point Exception",
                      "Virtualization Exception",
                      "Control Protection Exception",
                
                      "Unknown Interrupt",
                      "Unknown Interrupt",
                      "Unknown Interrupt",
                      "Unknown Interrupt",
                      "Unknown Interrupt",
                      "Unknown Interrupt",
                      
                      "Hypervisor Injection Exception",
                      "VMM Communication Exception",
                      "Security Exception",
                      "Unknown Interrupt"};

void remap_pic() {
    outportb(MASTER_PIC_COMMAND, PIC_INIT);         // Initialize on IO base address for Master PIC
    outportb(SLAVE_PIC_COMMAND, PIC_INIT);          // Initialize on IO base address for Slave PIC
    outportb(MASTER_PIC_DATA, MASTER_PIC_OFFSET);   // Master vector offset (starting at 32 since 0-31 exceptions)
    outportb(SLAVE_PIC_DATA, SLAVE_PIC_OFFSET);     // Slave vector offset
    outportb(MASTER_PIC_DATA, 0x04);                // Tells Master there is Slave PIC at IRQ2
    outportb(SLAVE_PIC_DATA, 0x02);                 // Slave PIC cascade identity
    outportb(MASTER_PIC_DATA, PIC_8086_MODE);       // Additional Master PIC environment info
    outportb(SLAVE_PIC_DATA, PIC_8086_MODE);        // Additional Slave PIC environment info
    outportb(MASTER_PIC_DATA, DEFAULT_MASTER_MASK); // Mask for Master PIC
    outportb(SLAVE_PIC_DATA, DEFAULT_SLAVE_MASK);   // Mask for Slave PIC
}   

void default_exception_handler(interruptFrame *frame) {
    disable_interrupts();
    terminal_writestring("EXCEPTION - ERROR CODE\n");
}

void default_interrupt_handler() {
    terminal_writestring("DEFAULT INTERRUPT\n");
}

void interrupt_handler(interruptFrame *frame) {
    if (frame->interrupt >= 32 && frame->interrupt <= 47) {
        if (frame->interrupt >= 40) {
            outportb(0xA0, 0x20);
        }

        outportb(0x20, 0x20);

        terminal_writestring("INTERRUPT\n");
    } else if (frame->interrupt <=31) {
        terminal_writestring("EXCEPTION\n");
    }
}