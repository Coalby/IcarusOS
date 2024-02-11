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
        "push %eax;"
        "movw $0x10, %ax;"
        "movw %ax, %ds;"
        "movw %ax, %es;"
        "movw %ax, %fs;"
        "movw %ax, %gs;"
        "pop %eax;"
    );
}

// Make sure to also call pop_general_reg()
void push_general_reg() {
    __asm__ ("popal;");
}

void pop_general_reg() {
    __asm__ ("pushal;");
}