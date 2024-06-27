#pragma once

#include "audioevent.h"
#include "iodef.h"
#include <exception>
#include <mutex>


class AudioEventQueue {
public:
    using event_q = std::priority_queue<AudioEvent, std::vector<AudioEvent>, AudioEventCompare>;
    AudioEventQueue() {};
    AudioEventQueue(const AudioEventQueue &) = default;
    AudioEventQueue(AudioEventQueue &&) = default;
    AudioEventQueue& operator=(const AudioEventQueue &) = default;
    AudioEventQueue& operator=(AudioEventQueue &&) = default;

    inline float Out() {
        float out = AudIO::SampleSilence;
        auto val = Clockbase::current_time.load();
        if (!next_event.has_value()) return out;
        if (val == (next_event.value().start_time \
            + next_event.value().duration - 1)) {
            event_active = false;
            event_index = 0;
            queue.pop();
            if (queue.empty()) {
                next_event = {};
            } else {
                next_event = queue.top();
            }
        } else if (val == next_event.value().start_time) {
            event_active = true;
        }
        if (event_active) {
            out = next_event.value().data->at(event_index);
            event_index++;
        }
        return out;

    }

    void add_event (const AudioEvent&& evt);

    AudioEvent_opt                                  next_event      {};
private:
    event_q                                         queue           {};
    uint32_t                                        event_index     {};
    bool                                            event_active    {};
    
};
