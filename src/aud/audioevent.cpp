#include "audioevent.h"
#include "clockbase.h"

AudioEvent* audio_event(AAllocator& alloc, SoundRes* res, Timestamp_t start) {
    AudioEvent*  event = (AudioEvent*) allocate_aa(alloc, sizeof(AudioEvent));
    
    if (SoundRes::WAV == res->type) {
        event->duration   = res->data.wav->len_data;
        event->data   = res->data.wav->data;
        event->stereo = (res->data.wav->numChannels == 2);
    }

    event->start_time = start;
    event->end_time = event->start_time + event->duration - 1;
    event->offset = 0;
    event->fade_in = CurveModel{.shape = unity, .length = 1, .offset = 0, 
                                        .start = 1, .end = 1, .bend = 0};
    event->fade_out = CurveModel{.shape = unity, .length = 1, .offset = event->end_time - event->fade_out.length, 
                                        .start = 1, .end = 1, .bend = 0};

    return event;
}

bool AudioEventCompare (const AudioEvent* lhs, const AudioEvent* rhs) {
        return lhs->start_time < rhs->start_time;
};
