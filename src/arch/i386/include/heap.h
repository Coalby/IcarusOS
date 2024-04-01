// TODO: This is NOT currently in use anywhere but is necessary once a 
//          Virtual memory manager is introduced to Icarus

#pragma once

#include <stdint.h>

// TODO: Initialize with address from physical memory manager
static uint32_t *cur_heap_position;

// Error handling is done by returning a NULL pointer, 
//  verifying that the size was allcated correctly
void *alloc(uint32_t size) {
    uint32_t *addr = cur_heap_position;
    cur_heap_position += size;
    return (void *) addr;
}

void free(void *ptr) {
    return;
}