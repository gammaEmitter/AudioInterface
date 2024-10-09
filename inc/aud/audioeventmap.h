#pragma once

#include "audioevent.h"
#include "clockbase.h"
#include "iodef.h"
#include <exception>
#include <mutex>
#include <map>


class AudioEventMap {
public:
    AudioEventMap() {};
    AudioEventMap(const AudioEventMap &) = default;
    AudioEventMap(AudioEventMap &&) = default;
    AudioEventMap& operator=(const AudioEventMap &) = default;
    AudioEventMap& operator=(AudioEventMap &&) = default;

    inline float Out() {
        float out = AudIO::SampleSilence;
        Timestamp_t curr_time = Clockbase::current_time.load();
        if (Clockbase::loop_pivot)  {
            curr_event = {}; 
            event_active = false;
        }
        if (!curr_event.has_value())  {
            if (Clockbase::loop_pivot) {
                auto idx = find_active_event(curr_time,events);
                if (idx != -1) {
                    curr_event = events[idx];
                    event_index = curr_time - events[idx].start_time;
                    event_active = true;
                }
            } else {
                auto idx = find_start_event(curr_time, events);
                if (idx != -1) {
                    curr_event = events[idx];
                    event_active = true;
                } else {
                    return out;
                }
            }
        } else {
                if (curr_time == curr_event.value().end_time) {
                    event_active = false;
                    event_index = 0;
                    curr_event = {};
                }
        }
        if (event_active) {
            try {
                out = curr_event.value().Out(event_index);
            }
            catch (const std::exception&) {
                printf("we should not be here\n");
                exit(1);
            }
            event_index++;
        }
        return out;
    }

    void add_event (const AudioEvent&& evt);

    AudioEvent_opt                                  curr_event      {};
private:
    std::vector<AudioEvent>                         events          {};
    u32                                             event_index     {};
    bool                                            event_active    {};
    
};
 
