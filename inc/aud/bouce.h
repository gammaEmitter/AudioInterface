#pragma once

#include "../allocator.h"
#include "clockbase.h"
#include "iodef.h"
#include "mixer.h"

struct BounceOffline {
    SignalPath path {};
    float* buffer {};
    Timestamp_t start {};
    Timestamp_t end {};
    u32 duration {};
    u32 index {};
    bool stereo {false};
    bool active {false};
};


void init_bounce_offline(AAllocator& alloc, BounceOffline*& bounce, Timestamp_t start, Timestamp_t end, bool stereo);

void out_bounce(void* arg);
