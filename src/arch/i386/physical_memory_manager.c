#include <physical_memory_manager.h>

// TODO: Implement parameters for mem_map_base_address and mem_size ; Keep them constant
//       Replace MAX_BLOCKS with parameters
void init_memory_manager() {
    memory_map = (uint32_t *)SYSTEM_BASE_ADDRESS;
    
    memset(memory_map, 0xFF, MAX_BLOCKS / BLOCKS_PER_BYTE);
}

// Initializes region of memory set by parameters (sets region as available)
void init_memory_region(const uint32_t base_address, const uint32_t size) {
    uint32_t mem_offset = base_address / BLOCK_SIZE;
    uint32_t num_blocks = size / BLOCK_SIZE;

    for (;num_blocks > 0; num_blocks--) {
        unset_block(mem_offset++);
    }
}

// Deinitializes region of memory set by parameters (sets region as reserved)
void deinit_memory_region(const uint32_t base_address, const uint32_t size) {
    uint32_t mem_offset = base_address / BLOCK_SIZE;
    uint32_t num_blocks = size / BLOCK_SIZE;

    for (;num_blocks > 0; num_blocks--) {
        set_block(mem_offset++);
    }
}