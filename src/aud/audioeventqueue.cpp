#include "audioeventqueue.h"


void AudioEventMap::add_event (const AudioEvent&& evt) {
    // if in range evt.start_time + evt.start_time + evt.duration
    // there is (THERE ARE MULTIPLE?) other events, override and adjust duration
    // of the OTHER events. this new event will fully covered
    e_map.emplace(evt.start_time, std::move(evt)); 
}
