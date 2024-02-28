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
.equ memmap_entries, 0x8500
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

        jmp _get_mem_map

        mov %cr0, %eax  
        or $1 ,%eax             # set PE (Protection Enable) bit in CR0 (Control Register 0)
        mov %eax, %cr0          # Enable Protected Mode
        
        ljmp $0x08, $start32


_get_mem_map:
        mov $0x8504, %di
        xor %ebx, %ebx
        xor %bp, %bp
        mov $0x534D4150, %edx
        mov $0xE820, %eax
        mov $1, %es:20(%di)
        mov $24, %ecx

        int $0x15
        jc .error

        cmp $0x534D4150, %eax
        jne .error
        test %ebx, %ebx
        jz .error

        jmp .jmp_in

.jmp_in:
        jcxz .skip_entry
        mov %es:8(%di), %ecx
        or %es:12(%di), %ecx
        jz .skip_entry

.next_entry:
        mov $0x534D4150, %edx
        mov $24, %ecx
        mov $0xE820, %eax
        int $0x15

.skip_entry:
        test %ebx, %ebx
        jz .done
        jmp .next_entry

.error:
        stc
        ret

.done:
        mov %bp, (memmap_entries)
        clc

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
