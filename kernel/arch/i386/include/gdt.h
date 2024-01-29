#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stdbool.h>

// Good for GDT visualization
typedef struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;

    uint8_t access;
    // uint8_t accessed:1;
    // uint8_t readable_writable:1;
    // uint8_t direction:1;
    // uint8_t executable:1;
    // uint8_t descriptor:1;
    // enum PRIVILEGE_LEVEL dpl:2;
    // uint8_t present:1;

    // Flags and limit high
    uint8_t flags_limit_high;
    // uint8_t limit_high:4;
    // uint8_t reserved:1;
    // uint8_t long_mode:1;
    // uint8_t size:1;
    // uint8_t granualarity:1;

    uint8_t base_high;
} __attribute__((packed)) GDT_Value;

typedef struct {
    uint16_t limit;
    GDT_Value* base;
} __attribute__((packed)) GDT_ptr;

enum {
    NULL_SEGMENT,
    KMODE_CODE,
    KMODE_DATA
};

/*  Finding particular bits in an int
    Another convenient method to find particular bits in an int: value & (((1 << #ofBits) - 1) << startBit)
 */

#define GDT_LIMIT_LOW(limit)                (limit & 0xFFFF)
#define GDT_BASE_LOW(base)                  (base & 0xFFFF)
#define GDT_BASE_MID(base)                  ((base >> 16) & 0xFF)
#define GDT_ACCESS(access)                  (access)
#define GDT_FLAGS_LIMIT_HIGH(flags, limit)  (((limit >> 16) & 0xF) | (flags & 0xF0))
#define GDT_BASE_HIGH(base)                 ((base >> 24) & 0xFF)

extern void flush_gdt();

void set_gdt_entry(GDT_Value *, uint32_t,  uint32_t,  uint8_t,  uint8_t);
void initialize_GDT();

#endif
