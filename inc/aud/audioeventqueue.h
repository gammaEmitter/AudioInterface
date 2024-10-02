#pragma once

#include "audioevent.h"
#include "clockbase.h"
#include "iodef.h"
#include <exception>
#include <mutex>
#include <map>

class AudioEventMap {
public:
    using event_map = std::map<Timestamp_t, AudioEvent>;
    AudioEventMap() {};
    AudioEventMap(const AudioEventMap &) = default;
    AudioEventMap(AudioEventMap &&) = default;
    AudioEventMap& operator=(const AudioEventMap &) = default;
    AudioEventMap& operator=(AudioEventMap &&) = default;

    inline float Out() {
        float out = AudIO::SampleSilence;
        auto val = Clockbase::current_time.load();
        auto it = e_map.find(val);
        if (it != e_map.end()) {
            curr_event = it->second;
            event_active = true;
        }
        if (!curr_event.has_value()) return out;

        if (val == (curr_event.value().start_time \
            + curr_event.value().duration - 1)) {
            event_active = false;
            event_index = 0;
            curr_event = {};
        }
        if (event_active) {
            out = curr_event.value().data->at(event_index);
            event_index++;
        }
        return out;

    }

    void add_event (const AudioEvent&& evt);

    AudioEvent_opt                                  curr_event      {};
private:
    event_map                                       e_map           {};
    uint32_t                                        event_index     {};
    bool                                            event_active    {};
    
};
