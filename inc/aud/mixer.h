#pragma once
#include "iodef.h"
#include "allocator.h"

#define CHANNELS 128
#define SIGNALS_CHANNEL 32
#define SIGNALS (CHANNELS * SIGNALS_CHANNEL)
#define MIXBUSSES 32

struct MixBus {
    SignalPath path {};
    struct signal{
        float* mixer_out_path;
        float gain {1.f};
    } signals[SIGNALS_CHANNEL];
    u8 signals_in_use {};
};
/*
 *  Not a passive mixer but actually handling signal routing and triggering out_x functions
 *  which are stored in the path->proc function pointer.
 */
struct Mixer {
    /*
     *  128channels x 32signals == 4096signals
     */
    SignalPath* paths[SIGNALS] {};
    float out_signals[SIGNALS] {0.f};
    float* ch_signals[CHANNELS] {};
    u8 used_signals[CHANNELS] {0};
    u8 order_channel[CHANNELS] {0};
    u8 channels_in_use {};
};

void init_mixer(AAllocator& alloc, Mixer*& mixer);
void init_mixbus(AAllocator& alloc, MixBus*& bus);

float sum_mixer(Mixer*);
void sum_mixbus(void*);
/*
 *  returns the index of the SignalPath in the mixer
 */
u16 mixer_signal_add(Mixer*, SignalPath*, u8);
u8 mixbus_signal_add(MixBus*, float*);


