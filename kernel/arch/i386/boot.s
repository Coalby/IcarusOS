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

.section .text
.global _start
.type _start, @function
_start:

        # set up stack pointer (esp)
        mov $stack_top, %esp

        

        # Kernel
        call kernel_main
        
        # Infinite loop
        cli
.hang:  hlt
        jmp .hang

.size _start, . - _start
