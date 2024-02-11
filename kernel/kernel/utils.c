// Consider adding hlt to hang computer indefinitly
void disable_interrupts() {
    __asm__ (
        "cli;"
    );
}

void enable_interrupts() {
    __asm__ (
        "sti;"
    );
}

void ksegment_load() {
    __asm__ (
        "movw $0x10, %ax;"
        "movw %ax, %ds;"
        "movw %ax, %es;"
        "movw %ax, %fs;"
        "movw %ax, %gs;"
    );
    
}