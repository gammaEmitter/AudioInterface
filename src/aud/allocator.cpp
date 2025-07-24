#include "../allocator.h"
#include <cstddef>
#include <cstring>


void init_allocator(AAllocator& alloc, size_t sz_total) {
   alloc.offset = 0;
   alloc.mem = (u8*) calloc(sz_total,sizeof(u8));
   alloc.sz_total = sz_total;
   assert(alloc.mem != NULL && "Allocator Init failed");
}
void* allocate_aa(AAllocator& alloc, size_t sz) {
   if (alloc.sz_total < alloc.offset + sz) {
      fprintf(stderr, "AAllocator full: trying to allocate %zu bytes when only %zu are available!\n",
              sz, alloc.sz_total - alloc.offset);
      return NULL;
   }
   u8* base = alloc.mem + alloc.offset;
   printf("Allocated %zu bytes at offset %zu\n", sz, alloc.offset);
   alloc.offset += sz;
   return (void*) base;
}
