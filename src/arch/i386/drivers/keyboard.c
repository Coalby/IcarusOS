#include "keyboard.h"
#include <lib.h>

// TODO: Fix dependencies to allow for less decoupling
#include <physical_memory_manager.h>

// Keymaps from cavOS on github. Thanks malwarepad!

static const char characterTable[] = {
    0,    0,    '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
    '-',  '=',  0,    0x09, 'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',
    'o',  'p',  '[',  ']',  0,    0,    'a',  's',  'd',  'f',  'g',  'h',
    'j',  'k',  'l',  ';',  '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  0,    '*',  0x0F, ' ',  0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
    0,    0,    0,    0,    0,    '/',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0,    0,    0,    0,    0,    0,    0,    0x2C,
};

static const char shiftedCharacterTable[] = {
    0,    0,    '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',  '(',  ')',
    '_',  '+',  0,    0x09, 'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',
    'O',  'P',  '{',  '}',  0,    0,    'A',  'S',  'D',  'F',  'G',  'H',
    'J',  'K',  'L',  ':',  '"',  '~',  0,    '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  0,    '*',  0x0F, ' ',  0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0x1B, 0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0x0E, 0x1C, 0,    0,    0,
    0,    0,    0,    0,    0,    '?',  0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0,
    0,    0,    0,    0,    0,    0,    0,    0x2C,
};

static char buffer[MAX_BUFFER_SIZE];
static uint8_t buffer_index = 0;

// TODO: Implement boolean variable
static uint8_t alloc_flag = 0;

void keyboard_install() {
    registerIRQhandler(1, keyboard_handler);
}

void clear_buffer() {
    for (uint8_t buffer_clear_index = 0; buffer_clear_index < MAX_BUFFER_SIZE; buffer_clear_index++) {
            buffer[buffer_clear_index] = '\0';
    }

    buffer_index = 0;
}

void keyboard_handler(interruptFrame *frame) {
    unsigned char scancode;

    scancode = inportb(0x60);

    if (scancode & 0x80) {
        // TODO: Add handling for shift || alt || control keys
    } else {
        switch (scancode) {
            // case 0x0E:
            //     terminal_removechar();
            //     break;
            case 0x1E:
                terminal_writestring("\nSize (4kb Blocks) to allocate: ");

                alloc_flag = 1;
                break;
            case 0x17:
                terminal_putchar('\n');
                icarus_ascii();
                break;
            case 0x1C:
                terminal_putchar('\n');
                if (alloc_flag != 0) {
                    terminal_writestring("Blocks allocated: ");
                    printf_hex(uatoi(buffer));
                    terminal_writestring("Block Offset Address: ");
                    printf_hex(find_free_blocks(uatoi(buffer)));
                    alloc_flag = 0;
                }

                // TODO: Move this into global function in external file to reduce coupling
                terminal_setcolor(2);
                terminal_writestring("user@home:");
                terminal_setcolor(7);

                // terminal_writestring(buffer);
                clear_buffer();

                break;

            default:
                buffer[buffer_index] = characterTable[scancode];
                buffer_index++;
                terminal_putchar(characterTable[scancode]);
        }
    }
}