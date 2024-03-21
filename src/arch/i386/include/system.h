// Contains System Utility Functions
#pragma once

#include <stdint.h>

// memset: Write len # of bytes to a buffer
//
// Returns:
//   buffer

inline void *memset(void *buffer, const uint8_t byte, const uint32_t len) {
    uint8_t *ptr = (uint8_t *)buffer;

    for (uint32_t i = 0; i < len; i++)
        ptr[i] = byte;

    return buffer;
}

void outportb(uint16_t _port, uint8_t _data);
uint8_t inportb(uint16_t _port);

void disable_interrupts();
void enable_interrupts();
