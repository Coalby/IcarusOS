// A bitmap is utilized as the physical memory manager for IcarusOS
// Setting the state of a given page: O(1)
// Allocating a given page: O(N)
#pragma once

#include <stdint.h>
#include <kernel.h>

#define BLOCK_SIZE              4096        // 4 Kb
#define BLOCKS_PER_BYTE         8           // Each bit represents a block

#define SYSTEM_BASE_ADDRESS     0x00000000   
#define SYSTEM_MEM_SIZE         0xFFFFFFFF
#define MAX_BLOCKS              (SYSTEM_MEM_SIZE / BLOCK_SIZE)

static uint32_t *memory_map;    // Each memory map entry contains 32 blocks
static uint32_t max_blocks;
static uint32_t used_blocks;

// These are declared as inline due to their high amount of usage
// This increases memory speed at the cost of code size

void set_block(uint32_t bit) {
    memory_map[bit/32] |= (1 << (bit % 32));
}

void unset_block(uint32_t bit) {
    memory_map[bit/32] &= ~(1 << (bit % 32));
}

char view_block(uint32_t bit) {
    return (memory_map[bit/32] & (1 << (bit % 32)));
}

// TODO: There has to be a better way to iterate
void free(uint32_t bit, uint32_t size) {
    uint32_t curr_bit = bit;

    while (size != 0x00) {
        unset_block(curr_bit);

        curr_bit++;
        size--;
    }
}

// Maybe add last free block pointer?
// Returns base address of free block
// Returns -1 if no available region space
uint32_t find_free_blocks(const uint32_t size) {
    for (uint32_t index = 0; index < (MAX_BLOCKS / 32); index++) {
        uint32_t bit_offset = 0, free_region_size = 0;

        if (memory_map[index] != 0xFFFFFFFF) {
            while(bit_offset % 32 != 0) {
                while (view_block(bit_offset)) {
                    free_region_size++;

                    if (free_region_size == size) {
                        return (index * 32) + bit_offset;
                    }
                }

                bit_offset += free_region_size + 1;
                free_region_size = 0;
            }
        }
    }

    // TODO: FIX THIS ASAP ; This assumes that the first block is always utilized
    return 0;
}

// Takes the necessary amount of blocks as size parameter and allocates memory space
inline void allocate(const uint32_t size) {
    uint32_t block_offset = find_free_blocks(size);

    if (block_offset == 0) {
        terminal_writestring("Cannot allocate memory; Not enough memory space!");
        return;
    } 

    // TODO: Fix iteration
    // while (size != 0x00) {
    //     set_block(block_offset);

    //     block_offset++;
    //     size--;
    // }

    return;
}

void init_memory_manager();