#include "iodef.h"
#include "allocator.h"

struct Delay{
    SignalPath path;
    float* buf;
    uint32_t duration;
    uint32_t cur_read;
    uint32_t cur_write;
    float wet;
    float dry;
    float gain;
    float feedback;
};

void init_delay(AAllocator& alloc, Delay* delay, uint32_t duration);

inline void out_delay(void* args) {
    Delay* delay = (Delay*) args;
    if (delay->path.in == nullptr) return;
    *delay->path.out = (delay->buf[delay->cur_read] * delay->wet + *delay->path.in * delay->dry) * delay->gain;
    delay->buf[delay->cur_write] = *delay->path.in + delay->buf[delay->cur_read] * delay->feedback; 
    // delay->buf[delay->cur_write] = *delay->path.in;
    if (++delay->cur_write > delay->duration) delay->cur_write = 0; //SIZE is duration + 1, 
                                                                    //so duration is valid index
    if (++delay->cur_read > delay->duration) delay->cur_read = 0;
}
