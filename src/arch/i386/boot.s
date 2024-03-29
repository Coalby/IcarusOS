 # Multiboot header constants
.set ALIGN,    1<<0
.set MEMINFO,   1<<1
.set FLAGS,   ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

# Declare multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate stack
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .data

# Declare GDT (Global Descriptor Table)
gdtr:
        .word 0xFFFF
        .long gdt_base

.align 4
gdt_base:
        /* Null Descriptor */
        .quad 0

        /* Kernel Code Descriptor */
        .word 0xFFFF
        .word 0
        .byte 0
        .byte 0x9a
        .byte 0xCF
        .byte 0

        /*  Kernel Data Descriptor */
        .word 0xFFFF
        .word 0
        .byte 0
        .byte 0x92
        .byte 0xCF
        .byte 0

.section .text
.globl _start
.type _start, @function
_start:
        cli

        lgdt (gdtr)

        mov %cr0, %eax  
        or $1 ,%eax             # set PE (Protection Enable) bit in CR0 (Control Register 0)
        mov %eax, %cr0          # Enable Protected Mode
        
        ljmp $0x08, $start32

.code32
start32:
        # Reload segment registers
        movw $0x10, %ax
        movw %ax, %ds
        movw %ax, %es
        movw %ax, %fs
        movw %ax, %gs
        movw %ax, %ss

        # set up stack pointer (esp)
        mov $stack_top, %esp
        
        # Kernel
        call kernel_main
        
        # Infinite loop
        cli
.hang:  hlt
        jmp .hang

.size _start, . - _start
