// A bitmap is utilized as the physical memory manager for IcarusOS
// Setting the state of a given page: O(1)
// Allocating a given page: O(N)
#pragma once

#include <stdint.h>
#include <system.h>
#include <kernel.h>

#define BLOCK_SIZE              4096        // 4 Kb
#define BLOCKS_PER_BYTE         8           // Each bit represents a block

#define SYSTEM_BASE_ADDRESS     0x00000000   
#define SYSTEM_MEM_SIZE         0xFFFFFFFF
#define MAX_BLOCKS              (SYSTEM_MEM_SIZE / BLOCK_SIZE)

static uint32_t *memory_map;    // Each memory map entry contains 32 blocks

// These are declared as inline due to their high amount of usage
// This increases memory speed at the cost of code size

static inline void set_block(uint32_t bit) {
    memory_map[bit/32] |= (1 << (bit % 32));
}

static inline void unset_block(uint32_t bit) {
    memory_map[bit/32] &= ~(1 << (bit % 32));
}

static inline char view_block(uint32_t bit) {
    return (memory_map[bit/32] & (1 << (bit % 32)));
}

// TODO: There has to be a better way to iterate
static inline void free(uint32_t bit, uint32_t size) {
    uint32_t curr_bit = bit;

    while (size != 0x00) {
        unset_block(curr_bit);

        curr_bit++;
        size--;
    }
}

// Returns base address of free block
// Returns -1 if no available region space
// TODO: Fix 128 kb limitation of saved information
// TODO: Iterate over ENTIRE memory map instead of just 32 blocks at a time
static inline int32_t find_free_blocks(const uint32_t size) {
    for (uint32_t index = 0; index < (MAX_BLOCKS / 32); index++) {
        if (memory_map[index] != 0xFFFFFFFF) {
            for (uint32_t bit_offset = 0, free_region_size = 0; bit_offset < 32; bit_offset++) {
                uint32_t mask = 1 << bit_offset;

                // Checks if block is set to zero
                if (!(memory_map[index] & mask)) {
                    free_region_size++;

                    if (free_region_size == size) {
                        // printf_hex((index * 32) + bit_offset);
                        return (index * 32) + bit_offset;
                    }
                } else {
                    free_region_size = 0;
                }
            }
        }
    }

    return -1;
}

// Takes the necessary amount of blocks as size parameter and allocates memory space

void init_memory_manager();
void init_memory_region(const uint32_t base_address, const uint32_t size);
void deinit_memory_region(const uint32_t base_address, const uint32_t size);