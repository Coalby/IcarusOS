#include <physical_memory_manager.h>

// TODO: Implement parameters for mem_map_base_address and mem_size ; Keep them constant
//       Replace MAX_BLOCKS with parameters
void init_memory_manager() {
    memory_map = (uint32_t *)SYSTEM_BASE_ADDRESS;
    
    memset(memory_map, 0xFF, MAX_BLOCKS / BLOCKS_PER_BYTE);
}

// Initializes region of memory set by parameters (sets region as available in memory map)
void init_memory_region(const uint32_t base_address, const uint32_t size) {
    uint32_t mem_offset = base_address / BLOCK_SIZE;
    uint32_t num_blocks = size / BLOCK_SIZE;

    for (;num_blocks > 0; num_blocks--) {
        unset_block(mem_offset++);
    }

    // TODO: This is ugly and needs to be reformated for better readability
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Initialized memory region...\n");
    terminal_writestring("Base Address: ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    printf_hex(base_address);
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Size: ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    printf_hex(size);
}

// Deinitializes region of memory set by parameters (sets region as reserved in memory map)
void deinit_memory_region(const uint32_t base_address, const uint32_t size) {
    uint32_t mem_offset = base_address / BLOCK_SIZE;
    uint32_t num_blocks = size / BLOCK_SIZE;

    for (;num_blocks > 0; num_blocks--) {
        set_block(mem_offset++);
    }

    // TODO: This is ugly and needs to be reformated for better readability
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Deinitialized memory region...\n");
    terminal_writestring("Base Address: ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    printf_hex(base_address);
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Size: ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    printf_hex(size);
}