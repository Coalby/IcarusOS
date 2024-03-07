// A bitmap is utilized as the physical memory manager for IcarusOS
// Setting the state of a given page: O(1)
// Allocating a given page: O(N)
#pragma once

#include <stdint.h>
#include <kernel.h>

#define BLOCK_SIZE          4096        // 4 Kb
#define BLOCKS_PER_BYTE     8           // Each bit represents a block

static uint32_t *memory_map;    // Each memory map entry contains 32 blocks
static uint32_t max_blocks;
static uint32_t used_blocks;

// These are declared as inline due to their high amount of usage
// This increases memory speed at the cost of code size

inline void set_block(uint32_t bit) {
    memory_map[bit/32] |= (1 << (bit % 32));
}

inline void unset_block(uint32_t bit) {
    memory_map[bit/32] &= -(1 << (bit % 32));
}

inline bool view_block(uint32_t bit) {
    return (memory_map[bit/32] & (1 << (bit % 32)));
}

// Takes the necessary amount of blocks as size parameter and allocates memory space
inline void malloc(uint32_t size) {
    uint32_t block_offset = find_free_blocks(size);

    if (block_offset == -1) {
        terminal_writestring("Cannot allocate memory; Not enough memory space!");
        return;
    } 
    

    // TODO: Mark as used
    // TODO: Return address
}

inline void free(uint32_t bit) {
    // TODO: Find the block  
    // TODO: unset all 
    
}

// Maybe add last free block pointer?
// Returns -1 if no available region space
inline uint32_t find_free_blocks(uint32_t size) {
    uint32_t *mem_iter = memory_map;
    uint32_t block_offset = 0, free_region_size = 0;

    while (*mem_iter != '\0') {
        while (view_block(block_offset)) {
            free_region_size++;

            if (free_region_size == size) {
                return block_offset - size;
            }
        }

        free_region_size = 0;
    }

    return -1;
}

// TODO: Implement GRUB memory map loader for address
void init_memory_manager(uint32_t start_address, uint32_t mem_map_size) {
    memory_map = (uint32_t *)start_address;
}