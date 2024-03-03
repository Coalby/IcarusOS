// Contains System Utility Functions
#pragma once

#include <stdint.h>

void outportb(uint16_t _port, uint8_t _data);
uint8_t inportb(uint16_t _port);

void disable_interrupts();
void enable_interrupts();
