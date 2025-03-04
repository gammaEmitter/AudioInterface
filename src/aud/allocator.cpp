#include "../allocator.h"


void init_allocator(AAllocator& alloc, size_t sz_total) {
   alloc.mem = (u8*) calloc(sz_total,sizeof(u8));
   assert(alloc.mem != NULL && "Allocator Init failed");
}
void* allocate_aa(AAllocator& alloc, size_t sz) {
   u8* base = alloc.mem + alloc.offset;
   alloc.offset += sz;
   return (void*) base;
}
