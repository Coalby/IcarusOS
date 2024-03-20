#include "physical_memory_manager.h"

// TODO: Implement parameters for mem_map_base_address and mem_size ; Keep them constant
//       Replace MAX_BLOCKS with parameters
void init_memory_manager() {
    memory_map = (uint32_t *)SYSTEM_BASE_ADDRESS;
    
    // memset(memory_map, 0xFF, MAX_BLOCKS / BLOCKS_PER_BYTE);
}