.code32

.p2align 4
.global isr0
isr0:
    num=0
    .rept 32
    .p2align 4
    .if ((1 << num) & 0x7D00)
        pushl $0
    .endif
    pushl $num-128
    jmp isr
    num=num+1
    .endr

    .rept 256-32
    .p2align 4
    pushl $0
    pushl $num-128
    jmp isr
    num=num+1
    .endr

.extern interrupt_handler
isr:
    push %eax
    push %ecx
    push %edx
    push %ebx
    push %esp
    push %ebp
    push %esi
    push %edi
    push %ds
    push %es
    push %fs
    push %gs

    # load kernel data segment
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    call interrupt_handler
    addl $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds
    pop %edi
    pop %esi
    pop %ebp
    pop %esp
    pop %ebx
    pop %edx
    pop %ecx
    pop %eax

    add $8, %esp
    
    iret