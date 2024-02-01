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
.align 4
# TODO: Finish idtr and idtr_gates to implement idt
idtr:

idtr_gates:
        
gdtr:
        .word gdtr-gdt_base-1
        .long gdt_base

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
.global _start
.type _start, @function
_start:

        # set up stack pointer (esp)
        mov $stack_top, %esp
        
        lgdt (gdtr)
        lidt (idtr)
        
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
        
        # Kernel
        call kernel_main
        
        # Infinite loop
        cli
.hang:  hlt
        jmp .hang

.size _start, . - _start
