global reload_segments

#define system_code_selector (1 << 3)
#define system_data_selector (2 << 3)

reload_segments:
    # Reload CS register containing code selector
    # both CS and DS should be zero at this point

    jmp system_code_selector, .reload_cs
.reload_cs:
    # Reload data segment registers
    movw system_data_selector, %ax
    movw ax, ds
    movw ax, es
    movw ax, fs
    movw ax, gs
    movw ax, ss
    ret