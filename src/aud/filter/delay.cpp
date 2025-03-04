#include "filter/delay.h"

void init_delay(AAllocator& alloc, Delay* delay, uint32_t duration) {
   
   delay->duration = duration;
   delay->cur_read = 0;
   delay->cur_write = duration;
   delay->dry = 0.5;
   delay->wet = 0.25;
   delay->gain = 0.7;
   delay->feedback = 0.3;
   delay->path.proc = &out_delay;
}
