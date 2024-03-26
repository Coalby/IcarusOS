#pragma once

#include <stdint.h>

// TODO: Initialize with address from physical memory manager
static uint8_t *cur_heap_position;

// Error handling is done by returning a NULL pointer, 
//  verifying that the size was allcated correctly
void *alloc(uint32_t size) {
    uint8_t *addr = cur_heap_position;
    cur_heap_position += size;
    return (void *) addr;
}

void free(void *ptr) {
    return;
}