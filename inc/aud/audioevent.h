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
    Timestamp_t                     end_time            {};
    uint32_t                        duration            {};
    std::vector<float>*             data                {};

    AudioEvent(const AudioEvent &) = default;
    AudioEvent(AudioEvent && other) {
        start_time = other.start_time;
        end_time = other.end_time;
        duration = other.duration;
        data = other.data;
    };
    AudioEvent &operator=(const AudioEvent &) = default;
    AudioEvent &operator=(AudioEvent &&) = default;
    AudioEvent(SoundRes *wav, Timestamp_t start);

  private:
    AudioEvent() = default;

};

using AudioEvent_opt = std::optional<AudioEvent>;

bool AudioEventCompare (const AudioEvent& lhs, const AudioEvent& rhs);





