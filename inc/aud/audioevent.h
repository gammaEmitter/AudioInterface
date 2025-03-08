#pragma once
#include "iodef.h"
#include "clockbase.h"
#include "ringbuffer.h"
#include "resourcemanager.h"
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
    float*                          data                {};
    CurveModel                      fade_in             {};
    CurveModel                      fade_out            {};
    bool                            stereo              {};

};

AudioEvent* audio_event(AAllocator& alloc, SoundRes *wav, Timestamp_t start);

inline float out_audio_event(AudioEvent* ev, u32 index) {
    if(index > ev->duration)  {
        printf("index %d out of range %d\n", index, ev->duration);
        return AudIO::SampleSilence;
    }
    float out = ev->data[index + ev->offset];
    if (out >= 1) {
        printf("index: %d duration: %d value: %f offset: %d\n", index, ev->duration, out, ev->offset);
        return AudIO::SampleSilence;
    }
    if (index >= ev->fade_in.offset && index <= (ev->fade_in.offset + ev->fade_in.length)) {
        float pos = (float)index / ev->fade_in.length;
        out *= out_curve(&ev->fade_in, pos); 
    } else if (index >= ev->fade_out.offset && index <= (ev->fade_out.offset + ev->fade_out.length)) {
        float pos = (float)index / ev->fade_out.length;
        out *= out_curve(&ev->fade_out, pos); 
    }
    return out;
}
using AudioEvent_opt = std::optional<AudioEvent>;

bool AudioEventCompare(const AudioEvent* lhs, const AudioEvent* rhs);





