.code32

.macro ERROR_CODE num
.globl isr\num
isr\num:
    pushl $\num         # interrupt number
    jmp isr
.endm

.macro NO_ERROR_CODE num
.globl isr\num
isr\num:
    pushl $0            # dummy error code
    pushl $\num         # interrupt number
    jmp isr
.endm

.macro IRQ num
.globl isr\num
isr\num:
    pushl $0            # dummy error code
    pushl $\num         # interrupt number
    jmp irq
.endm

# exceptions and CPU reserved interrupts 0 - 31
NO_ERROR_CODE 0
NO_ERROR_CODE 1
NO_ERROR_CODE 2
NO_ERROR_CODE 3
NO_ERROR_CODE 4
NO_ERROR_CODE 5
NO_ERROR_CODE 6
NO_ERROR_CODE 7
ERROR_CODE    8
NO_ERROR_CODE 9
ERROR_CODE    10
ERROR_CODE    11
ERROR_CODE    12
ERROR_CODE    13
ERROR_CODE    14
NO_ERROR_CODE 15
NO_ERROR_CODE 16
NO_ERROR_CODE 17
NO_ERROR_CODE 18
NO_ERROR_CODE 19
NO_ERROR_CODE 20
NO_ERROR_CODE 21
NO_ERROR_CODE 22
NO_ERROR_CODE 23
NO_ERROR_CODE 24
NO_ERROR_CODE 25
NO_ERROR_CODE 26
NO_ERROR_CODE 27
NO_ERROR_CODE 28
NO_ERROR_CODE 29
NO_ERROR_CODE 30
NO_ERROR_CODE 31

# IRQs
IRQ 32
IRQ 33
IRQ 34
IRQ 35
IRQ 36
IRQ 37
IRQ 38
IRQ 39
IRQ 40
IRQ 41
IRQ 42
IRQ 43
IRQ 44
IRQ 45
IRQ 46
IRQ 47

.globl _pushalgen
.type _pushalgen, @function
_pushalgen:
    push %ds
    push %es
    push %fs
    push %gs
    ret

.globl _popalgen
.type _popalgen, @function
_popalgen:
    pop %gs
    pop %fs
    pop %es
    pop %ds
    ret

.globl _pushald
.type _pushald, @function
_pushald:
    push %eax
    push %ecx
    push %edx
    push %ebx
    push %esp
    push %ebp
    push %esi
    push %edi
    ret

.globl _popald
.type _popald, @function
_popald:
    pop %edi
    pop %esi
    pop %ebp
    pop %esp
    pop %ebx
    pop %edx
    pop %ecx
    pop %eax
    ret

.extern default_exception_handler
isr:
    call _pushald
    call _pushalgen 

    # load kernel data segment
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call default_exception_handler

    call _popalgen
    call _popalgen
    
    iret

.extern default_interrupt_handler
irq:
    call _pushald
    call _pushalgen 

    # load kernel data segment
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call default_interrupt_handler

    call _popalgen
    call _popalgen

    iret

# TODO: Find better way to initialize table. Good loop examples on NASM are common
.globl idt_stub_table
idt_stub_table:
    .long isr0
    .long isr1
    .long isr2
    .long isr3
    .long isr4
    .long isr5
    .long isr6
    .long isr7
    .long isr8
    .long isr9
    .long isr10
    .long isr11
    .long isr12
    .long isr13
    .long isr14
    .long isr15
    .long isr16
    .long isr17
    .long isr18
    .long isr19
    .long isr20
    .long isr21
    .long isr22
    .long isr23
    .long isr24
    .long isr25
    .long isr26
    .long isr27
    .long isr28
    .long isr29
    .long isr30
    .long isr31
    .long isr32
    .long isr33
    .long isr34
    .long isr35
    .long isr36
    .long isr37
    .long isr38
    .long isr39
    .long isr40
    .long isr41
    .long isr42
    .long isr43
    .long isr44
    .long isr45
    .long isr46
    .long isr47