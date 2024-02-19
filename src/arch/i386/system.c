#include "system.h"

void outportb(uint16_t _port, uint8_t _data) {
    __asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}

uint8_t inportb(uint16_t _port) {
    uint8_t rv;
  __asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
  return rv;
}

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