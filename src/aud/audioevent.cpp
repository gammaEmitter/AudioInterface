#include "audioevent.h"
#include "clockbase.h"
#include "soundresource.h"
#include <variant>

AudioEvent* audio_event(AAllocator& alloc, SoundRes* res, Timestamp_t start) {
    AudioEvent*  event = (AudioEvent*) allocate_aa(alloc, sizeof(AudioEvent));
    
    std::visit<>([&event](auto&& arg){
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, WavTool::RiffWAV>) {
            event->duration   = arg.data.size();
            event->data       = &arg.data;
        }
    },res->value());

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
