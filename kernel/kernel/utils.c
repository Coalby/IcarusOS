// Consider adding hlt to hang computer indefinitly
void disable_interrupts() {
    __asm__ __volatile__ (
        "cli;"
    );
}