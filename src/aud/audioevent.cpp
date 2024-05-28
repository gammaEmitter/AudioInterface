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
}

/*
 *  Creates a Timestamp from a position in th beat-grid
 *   Ticks range from 0 to 63
 */
Timestamp_t timeFromBeats(uint16_t beats, uint8_t ticks) {

    int tick64_length = Clockbase::beat_length() / 64;
    Timestamp_t time = (beats * Clockbase::beat_length()) + (ticks * tick64_length);
    return time;
}
