#pragma once

#include <atomic>
#include "iodef.h"
#include <cstddef>

/*
*   Timebase incremented from PortAudio-Callback
*/

using Timestamp_t = u32;

namespace Clockbase {

    extern std::atomic<Timestamp_t>         current_time;

    extern std::atomic<size_t>              samples_passed;     // 0 - 44100

    extern SampleRate_t                     samplerate;

    extern uint8_t                          tempo;
    
    extern bool                             loop_active;

    extern bool                             loop_pivot;

    extern Timestamp_t                      loop_in;

    extern Timestamp_t                      loop_out;

    static u16 beat_length() {
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

struct BeatUnit {
    u16 beats;
    uint8_t ticks;

    void operator+(BeatUnit& other) {
        beats += other.beats;
        ticks += other.ticks;
        if (ticks > 63) {
            beats += ticks / 64;
            ticks %= 64;
        }
    }
    void operator-(BeatUnit& other) {
        beats -= other.beats;
        ticks -= other.ticks;
        // TODO: implement
    }
};

Timestamp_t timeFromBeats(u16 beats, uint8_t ticks);
BeatUnit    beatsFromTime(Timestamp_t time);

struct TransportWatch {
    std::atomic<u16>               seconds         {};
    std::atomic<float>                  milliseconds    {};
    std::atomic<uint8_t>                tempo_ticks     {};
    std::atomic<u16>               beats           {};

    void refresh() {
        Timestamp_t currTime = Clockbase::current_time.load();
        seconds.store(currTime / Clockbase::samplerate);
        u16 beatlen = Clockbase::beat_length();
        milliseconds.store((float) (currTime % Clockbase::samplerate) / Clockbase::samplerate);
        beats.store(currTime / beatlen);
        int tick64_length = beatlen / 64;
        tempo_ticks.store(currTime % beatlen / beatlen);
    }
};

