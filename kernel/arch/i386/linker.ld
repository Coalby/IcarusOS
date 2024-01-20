ENTRY(_start)

SECTIONS {
    /* Set the base address to 0x00100000 */
    . = 0x00100000;

    /* .text section with 4 KB alignment */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* .rodata section with 4 KB alignment */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata*)
    }

    /* .data section with 4 KB alignment */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* .bss section with 4 KB alignment */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
