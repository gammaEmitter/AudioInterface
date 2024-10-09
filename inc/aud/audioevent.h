#pragma once

#include "iodef.h"
#include "clockbase.h"
#include "ringbuffer.h"
#include "soundresource.h"
#include "wavtool.h"
#include "curvetool.h"
#include <string>
#include <vector>
#include <optional>

class AudioEvent {
public:

    Timestamp_t                     start_time          {};
    Timestamp_t                     end_time            {};
    u32                             duration            {};
    u32                             offset              {};
    std::vector<float>*             data                {};
    CurveModel                      fade_in             {};
    CurveModel                      fade_out            {};

    AudioEvent(SoundRes *wav, Timestamp_t start);
    AudioEvent(const AudioEvent &) = default;
    AudioEvent(AudioEvent && other) {
        start_time = other.start_time;
        end_time = other.end_time;
        duration = other.duration;
        data = other.data;
        offset = other.offset;
        fade_in = other.fade_in;
        fade_out = other.fade_out;
    };
    AudioEvent &operator=(const AudioEvent &) = default;
    AudioEvent &operator=(AudioEvent &&) = default;

    inline float Out(u32 index) {
        float out = data->at(index + offset);

        if (index >= fade_in.offset && index <= (fade_in.offset + fade_in.length)) {
            float pos = (float)index / fade_in.length;
            out *= fade_in.out(pos);
        } else if (index >= fade_out.offset && index <= (fade_out.offset + fade_out.length)) {
            float pos = (float)index / fade_out.length;
            out *= fade_out.out(pos);
        }
        return out;
    }

  private:
    AudioEvent() = default;

};

using AudioEvent_opt = std::optional<AudioEvent>;

bool AudioEventCompare (const AudioEvent& lhs, const AudioEvent& rhs);





