#include "audioevent.h"
#include "clockbase.h"
#include <variant>

AudioEvent::AudioEvent(SoundRes* res, Timestamp_t start) {
    AudioEvent event {};
    
    std::visit<>([&event](auto&& arg){
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, WavTool::RiffWAV>) {
            event.duration   = arg.data.size();
            event.data       = &arg.data;
        }
    },res->value());

    duration = event.duration;
    data = event.data;
    start_time = start;
    end_time = start_time + duration - 1;

}

bool AudioEventCompare (const AudioEvent& lhs, const AudioEvent& rhs) {
        return lhs.start_time < rhs.start_time;
};
