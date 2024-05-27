#pragma once

#include <atomic>
#include "iodef.h"
//#include <_types/_uint32_t.h>
#include <cstddef>

/*
*   64-tick Timebase, incremented from PortAudio-Callback
*/

using Timestamp_t = uint32_t;

struct Clockbase {

    static std::atomic<Timestamp_t>         current_time;

    static std::atomic<size_t>              samples_passed;     // 0 - 44100
    static std::atomic<uint8_t>             time_ticks;         // 0 - 63 
    static std::atomic<uint16_t>            seconds;            // counts up
    static std::atomic<uint8_t>             tempo_ticks;        // 0 - 63 
    static std::atomic<uint16_t>            beats;              // counts up

    static constexpr SampleRate_t           samplerate      = AudIO::Samplerate44100;
    static constexpr uint8_t                amtTickPhases   = 4;            
    static constexpr uint8_t                amtTicks        = 64;

    static uint16_t                         counter;            // 0 - m_period
    static uint8_t                          tickphase;          // 0 - 3

    static uint8_t                          tempo;

    enum TickPeriod_44 {
                                            standard        = (int) samplerate / amtTicks,
                                            correction      = standard + 1,
    };
    
    static TickPeriod_44                    period;

    static size_t                           tempo_period;
    
    static inline void increment() {
        current_time++;
        ++counter;
        samples_passed++;
        if (samples_passed.load() == 44100) {
            samples_passed.store(0);
        }
        if (counter == period) {
            time_ticks++;
            if (time_ticks.load() == amtTicks) {
                seconds++; 
                time_ticks.store(0);
            }
            ++tickphase; 
            tickphase %= amtTickPhases;
            if (tickphase == 3) {
                period = correction;
                tempo_period = period * (60 / tempo);
            } else {
                period = standard;
                tempo_period = period * (60 / tempo);
            }
            counter = 0;
        }

    }
};


