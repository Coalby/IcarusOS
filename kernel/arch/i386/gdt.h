#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdbool.h>

// Good for GDT visualization
struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    struct {
        bool accessed:1;
        bool readable_writable:1;
        bool direction:1;
        bool executable:1;
        bool descriptor:1;
        bool privilege:2;
        bool present:1;
    } __attribute__((packed)) access;
    struct {
        uint8_t limit_high:4;
        bool reserved:1;
        bool long_mode:1;
        bool size:1;
        bool granualarity:1;
    } __attribute__((packed)) flags_limit_high;
    uint8_t base_high;
} __attribute__((packed)) GDT_Entry;

enum {
    NULL,
    KMODE_CODE,
    KMODE_DATA,
    TASKSTATE
};

#endif
