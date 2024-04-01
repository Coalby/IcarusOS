#include <stdbool.h>
#include <idt.h>
#include <pit.h>
#include <system.h>
#include <keyboard.h>
#include <physical_memory_manager.h>
#include "kernel.h"
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg  | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
    size_t size = 0;
    while(str[size]) size++;
    return size;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for(size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    terminal_buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_row = 0;
        }
    }
}

// TODO: Add edge cases
// TODO: Replace terminal_putentryat with a correct call to terminal_putchar
void terminal_removechar() {
    terminal_column--;
    terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}

// Only allows 2 Byte ouput
void printf_hex(const uint32_t num)
{
    const char hex_digits[] = "0123456789ABCDEF";
    uint8_t shift = 0;

    terminal_write("0x", 2);

    // Start from the most significant nibble
    while (shift < 32) {
        uint8_t digit = (num >> (28 - shift)) & 0xF; // Extract the nibble
        terminal_putchar(hex_digits[digit]); // Print the digit
        shift += 4;
    }

    terminal_putchar('\n');
}

void icarus_ascii() 
{
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("              /\\ _ /\\     \n");
    terminal_writestring("             ( * ^ *`)     \n");
    terminal_writestring("            _/ >     \\__  \n");
    terminal_writestring("          / `/   Y  (   \\   \n");
    terminal_writestring("         (  (  ` /\\ _/ ` )   \n");
    terminal_writestring("         |   /\\---`/    /  \n");
    terminal_writestring("          \\______>,_ _/    \n");
    terminal_writestring("             | `===` |    \n");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    terminal_writestring("\n               Bobo\n");
}

void kernel_main(void)
{   
    // Initialize kernel interface
    terminal_init();
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Kernel initialized...\n");

    init_idt();
    terminal_writestring("Interrupt descriptor table initialized...\n");
    
    timer_install((uint16_t) 100);
    terminal_writestring("Periodic interval timer initialized...\n");
    
    keyboard_install();
    enable_interrupts();
    terminal_writestring("Interrupts enabled...\n");

    init_memory_manager();
    init_memory_region(0x100000, 0x7EE0000);

    // icarus_ascii();

    // Infinite Hang
    for (;;) {
        
    }
}