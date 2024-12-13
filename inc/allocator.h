#pragma once
#include "iodef.h"

struct AAllocator {
    uint8_t* mem;
    size_t sz_total;  
    size_t offset;  
};
void init_allocator(AAllocator& alloc, size_t sz_total);
void* allocate_aa(AAllocator& alloc, size_t sz);
