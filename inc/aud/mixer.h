#pragma once
#include "iodef.h"
#include "../allocator.h"

struct Mixer {
    /*
     *  128channels x 32signals == 4096signals
     */
    SignalPath* paths[4096] {};
    float out_signals[4096] {0.f};
    float* ch_signals[128] {};
    u8 used_signals[128] {0};
    u8 order_channel[128];
    u8 channels_in_use {};
};

Mixer* init_mixer(AAllocator&);
float sum_mixer(Mixer*);
/*
 *  returns the index of the SampleOut_fn in the fn_signals array
 */
u16 mixer_signal_add(Mixer*, SignalPath*, u8);

