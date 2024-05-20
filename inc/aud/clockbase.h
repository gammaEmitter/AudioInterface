#include <atomic>
#include "iodef.h"
//#include <_types/_uint32_t.h>
#include <cstddef>

/*
*   64-tick Timebase, incremented from PortAudio-Callback
*/

struct Clockbase {

    static std::atomic<size_t>              ticks;           // 0 - 63 
    static std::atomic<uint32_t>            seconds;           // counts up

    static constexpr SampleRate_t           samplerate    = AudIO::Samplerate44100;
    static constexpr size_t                 amtTickPhases = 4;            
    static constexpr size_t                 amtTicks      = 64;

    enum TickPeriod_44 {
                                            standard        = (int) samplerate / amtTicks,
                                            correction      = standard + 1,
    };

    static uint32_t                         counter;            // 0 - m_period
    static size_t                           tickphase;            // 0 - 3
    static TickPeriod_44                    period;

    static float                            test_seconds;
    static int                              test_seconds_int;
    static int                              last_second;
    
    static inline void increment() {
        ++counter;
        if (counter == period) {
            ticks++;
            if (ticks.load() == amtTicks) {
                seconds++; 
                printf("%u\n", seconds.load());
                ticks.store(0);
            }
            ++tickphase; 
            tickphase %= amtTickPhases;
            if (tickphase == 3) {
                period = correction;
            } else {
                period = standard;
            }
            counter = 0;
        }
    }
};
