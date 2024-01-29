#include "gdt.h"

GDT_Value gdt[3];

void set_gdt_entry(GDT_Value* entry, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
    entry->limit_low        = GDT_LIMIT_LOW(limit);
    entry->base_low         = GDT_BASE_LOW(base);
    entry->base_mid         = GDT_BASE_MID(base);
    entry->access           = access;
    entry->flags_limit_high = GDT_FLAGS_LIMIT_HIGH(flags, limit);
    entry->base_high        = GDT_BASE_HIGH(base);
}

void initialize_GDT() {

    GDT_ptr gdt_ptr = {(sizeof(GDT_Value) - 1), gdt};

    // Null Descriptor is already set
    GDT_Value *entry = gdt;

    // Kernel Mode Code Segment
    set_gdt_entry(++entry, 0xFFFFF, 0x0, 0x9A, 0xC);

    // Kernel Mode Data Segment
    set_gdt_entry(++entry, 0xFFFFF, 0x0, 0x92, 0xC);

    __asm__ __volatile__ (
        "lgdt %0;"      // Load GDT
        :
        : "m" (gdt_ptr));

    flush_gdt();
}