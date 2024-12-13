#pragma once

#include "iodef.h"
#include "clockbase.h"
#include "ringbuffer.h"
#include "soundresource.h"
#include "wavtool.h"
#include "curvetool.h"
#include "../allocator.h"
#include <string>
#include <vector>
#include <optional>

struct AudioEvent {
    Timestamp_t                     start_time          {};
    Timestamp_t                     end_time            {};
    u32                             duration            {};
    u32                             offset              {};
    std::vector<float>*             data                {};
    CurveModel                      fade_in             {};
    CurveModel                      fade_out            {};
};

AudioEvent* audio_event(AAllocator& alloc, SoundRes *wav, Timestamp_t start);
// inline float out_audio_event(AudioEvent& ev, u32 index);
inline float out_audio_event(AudioEvent* ev, u32 index) {
    float out = ev->data->at(index + ev->offset);

    if (index >= ev->fade_in.offset && index <= (ev->fade_in.offset + ev->fade_in.length)) {
        float pos = (float)index / ev->fade_in.length;
        out *= ev->fade_in.out(pos);
    } else if (index >= ev->fade_out.offset && index <= (ev->fade_out.offset + ev->fade_out.length)) {
        float pos = (float)index / ev->fade_out.length;
        out *= ev->fade_out.out(pos);
    }
    return out;
}
using AudioEvent_opt = std::optional<AudioEvent>;

bool AudioEventCompare (const AudioEvent* lhs, const AudioEvent* rhs);





