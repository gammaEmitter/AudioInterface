#include "iodef.h"
#include "clockbase.h"
#include "ringbuffer.h"
#include <string>
#include <vector>

struct AudioEvent {

    size_t                          start_beats         {};
    uint32_t                        start_tempo_ticks   {};
    uint32_t                        duration            {};
    std::vector<float>*             audio_data          {};

};

struct AudioEventCompare {
 
    bool operator() (const AudioEvent& lhs, const AudioEvent& rhs) {
        if (lhs.start_beats < rhs.start_beats) return true;
        if (lhs.start_beats > rhs.start_beats) return false;

        if (lhs.start_tempo_ticks < rhs.start_tempo_ticks) return true;
        if (lhs.start_tempo_ticks > rhs.start_tempo_ticks) return false;

        return true;
    }
};



