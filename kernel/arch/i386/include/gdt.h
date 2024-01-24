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
    typedef struct {
        bool accessed:1;
        bool readable_writable:1;
        bool direction:1;
        bool executable:1;
        bool descriptor:1;
        bool privilege:2;
        bool present:1;
    } __attribute__((packed)) access;
    typedef struct {
        uint8_t limit_high:4;
        bool reserved:1;
        bool long_mode:1;
        bool size:1;
        bool granualarity:1;
    } __attribute__((packed)) flags_limit;
    uint8_t base_high;
} __attribute__((packed)) GDT_Entry;

enum {
    NULL,
    KMODE_CODE,
    KMODE_DATA,
    TASKSTATE
};

/*  A convenient method to find particular bits in an int: value & (((1 << #ofBits) - 1) << startBit)
 *  Added '<< 0' for readability, it does not do anything
 *  Could also use & 0xFFFF (Might be better)
 */

#define GDT_LIMIT_LOW(limit)                (limit & (((1 << 16) - 1) << 0))
#define GDT_BASE_LOW(base)                  (base & (((1 << 16) - 1) << 0))
#define GDT_BASE_MID(base)                  (base & (((1 << 8) - 1) << 16))
#define GDT_ACCESS(access)                  access
#define GDT_FLAGS_LIMIT_HIGH(flags, limit)  (limit & (((1 << 4) - 1) << 16))
#define GDT_BASE_HIGH                       (base & (((1 << 8) - 1) << 24))

#endif
