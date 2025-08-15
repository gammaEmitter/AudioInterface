#include "bouce.h"
#include "allocator.h"
#include "clockbase.h"
#include "iodef.h"


void init_bounce_offline(AAllocator& alloc, BounceOffline*& bounce, Timestamp_t start, Timestamp_t end, bool stereo = 2) {
   assert(start < end && "Invlid bounce bounds.");
   bounce = (BounceOffline*) malloc(sizeof(BounceOffline));

   bounce->start = start;
   bounce->end = end;
   bounce->duration = (end - start - 1) * (1 + stereo);
   float* mem = (float*) calloc(bounce->duration, sizeof(float));
   bounce->path.proc = &out_bounce;
   bounce->buffer = mem;
   bounce->index = 0;
} 

void out_bounce(void* arg) {
   BounceOffline* bounce = (BounceOffline*) arg;
   Timestamp_t cur_time = Clockbase::current_time.load();
   if (bounce->index > bounce->duration) {
      bounce->index = 0;
      bounce->active = false;
      printf("bounce index outstepped duration @ %d\n", cur_time);
      *bounce->path.out = *bounce->path.in;
      return;
   }
   if (bounce->start == cur_time) {
      bounce->active = true;
      printf("bounce active @ %d\n", cur_time);
   }
   if (bounce->end == cur_time) {
      bounce->index = 0;
      bounce->active = false;
      printf("bounce inactive @ %d\n", cur_time);
   }
   if (bounce->active) {
      bounce->buffer[bounce->index++] = *bounce->path.in;
   }
   *bounce->path.out = *bounce->path.in;
}
