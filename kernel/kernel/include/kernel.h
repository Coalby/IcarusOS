#pragma once

#include <stdint.h>
#include <stddef.h>

enum PRIVILEGE_LEVEL
{
    RING_0, RING_1, RING_2, RING_3
};

void terminal_init(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void kernel_main(void);