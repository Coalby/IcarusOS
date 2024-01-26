#include "gdt.h"
#include "tss.h"

GDT_Value gdt[] = {
    // NULL descriptor
    GDT_ENTRY(0, 0, 0, 0),

    // KMODE_CODE descriptor
    GDT_ENTRY(0, 0xFFFFF, 0x9A, 0xC),

    // KMODE_DATA descriptor
    GDT_ENTRY(0, 0xFFFFF, 0x92, 0xC),

    // TODO: TASKSTATE descriptor
};

GDT_ptr gdt_ptr = {(sizeof(GDT_Value) - 1), gdt};


