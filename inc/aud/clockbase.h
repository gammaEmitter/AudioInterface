#pragma once

#include <atomic>
#include "iodef.h"
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
    
    extern bool                             loop_active;

    extern bool                             loop_pivot;

    extern Timestamp_t                      loop_in;

    extern Timestamp_t                      loop_out;

    static uint16_t beat_length() {
        return samplerate * (60/(float)tempo);
    }

    static void increment() {
        if (loop_pivot) loop_pivot = false;
        auto curr_time = current_time.load();
        if (loop_active && curr_time >= loop_in) {
            if (curr_time == loop_out - 1) {
                current_time.store(loop_in);
                loop_pivot = true;
            } else {
                current_time++;
            }
        } else {
            current_time++;
        }
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
        uint16_t beatlen = Clockbase::beat_length();
        milliseconds.store((float) (currTime % Clockbase::samplerate) / Clockbase::samplerate);
        beats.store(currTime / beatlen);
        int tick64_length = beatlen / 64;
        tempo_ticks.store(currTime % beatlen / beatlen);
    }
};

