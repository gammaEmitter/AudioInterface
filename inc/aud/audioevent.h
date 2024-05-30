#pragma once

#include "iodef.h"
#include "clockbase.h"
#include "ringbuffer.h"
#include "soundresource.h"
#include "wavtool.h"
#include <string>
#include <vector>
#include <optional>

class AudioEvent {
public:
    Timestamp_t                     start_time          {};
    uint32_t                        duration            {};
    std::vector<float>*             data                {};

    AudioEvent(SoundRes* wav, Timestamp_t start);

private:
    AudioEvent() = default;

};

using AudioEvent_opt = std::optional<AudioEvent>;

struct AudioEventCompare {
 
    bool operator() (const AudioEvent& lhs, const AudioEvent& rhs) {
        return lhs.start_time > rhs.start_time;
    }
};





