.globl flush_gdt

flush_gdt:
    ljmp $0x08, $.flush_end
.flush_end:
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ret
