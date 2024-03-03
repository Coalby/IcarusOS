// A bitmap is utilized as the physical memory manager for IcarusOS
// Setting the state of a given page: O(1)
// Allocating a given page: O(N)
#pragma once

#include <stdint.h>

static uint32_t *memory_map;

#define BLOCK_SIZE          4096        // 4 Kb
#define BLOCKS_PER_BYTE     8           // Each bit represents a block

// These are declared as inline due to their high amount of usage
// This increases memory speed at the cost of code size

// TODO: Finish malloc function
inline void malloc(uint32_t bit) {
    uint32_t free_block;

    free_block = find_free_block();
}

// TODO: Finish find_free_block function
inline uint32_t find_free_block() {
    for (uint32_t bit; bit < memory_map[bit]; bit++) {
        if (memory_map[bit % 32] == 0x00) {
            return bit;
        }
    }
}

void init_memory_manager();