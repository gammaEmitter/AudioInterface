#pragma once

#include <atomic>
#include "iodef.h"
//#include <_types/_uint32_t.h>
#include <cstddef>

/*
*   Timebase incremented from PortAudio-Callback
*/

using Timestamp_t = uint32_t;

namespace Clockbase {

    extern std::atomic<Timestamp_t>         current_time;

    extern std::atomic<size_t>              samples_passed;     // 0 - 44100

    extern SampleRate_t                     samplerate;

    extern uint8_t                          tempo;

    static uint16_t beat_length() {
        return samplerate * (60/(float)tempo);
    }

    static void increment() {
        current_time++;
        samples_passed++;
        if (samples_passed.load() == samplerate) {
            samples_passed.store(0);
        }
    }
};

Timestamp_t timeFromBeats(uint16_t beats, uint8_t ticks);

struct TransportWatch {
    std::atomic<uint16_t>               seconds         {};
    std::atomic<float>                  milliseconds    {};
    std::atomic<uint8_t>                tempo_ticks     {};
    std::atomic<uint16_t>               beats           {};

    void refresh() {
        Timestamp_t currTime = Clockbase::current_time.load();
        seconds.store(currTime / Clockbase::samplerate);
        milliseconds.store((float) (currTime % Clockbase::samplerate) / Clockbase::samplerate);
        beats.store(currTime / Clockbase::beat_length());
        int tick64_length = Clockbase::beat_length() / 64;
        tempo_ticks.store(currTime % Clockbase::beat_length() / Clockbase::beat_length());
    }
};

