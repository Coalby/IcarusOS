.code32

.macro ISR_ERROR_CODE num
.globl isr\num
isr\num:
    pushl $\num        # interrupt number
    jmp isr_exceptions
.endm

.macro ISR_NO_ERROR_CODE num
.globl isr\num
isr\num:
    pushl $0         # dummy error code
    pushl $\num        # interrupt number
    jmp isr_exceptions
.endm

# exceptions and CPU reserved interrupts 0 - 31
ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE    8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE    10
ISR_ERROR_CODE    11
ISR_ERROR_CODE    12
ISR_ERROR_CODE    13
ISR_ERROR_CODE    14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_NO_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_NO_ERROR_CODE 30
ISR_NO_ERROR_CODE 31

isr_exceptions:
    push ds
    push es
    push fs
    push gs

    # load kernel data segment
    push eax
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    pop eax

    .extern default_exception_handler
    call default_exception_handler

    pop gs
    pop fs
    pop es
    pop ds
    iret

.globl stub_table
stub_table:
    i EQU 0
    %rep 32
        .long isr\i
    %assign i i+1
    %endrep
