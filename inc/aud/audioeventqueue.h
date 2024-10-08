#pragma once

#include "audioevent.h"
#include "clockbase.h"
#include "iodef.h"
#include <exception>
#include <mutex>
#include <map>

int find_active_event (Timestamp_t time, const std::vector<AudioEvent>& events);
int find_start_event(Timestamp_t time, const std::vector<AudioEvent>& events);

enum Intersect {
    none,
    cuts_end, // new event cuts end of existing event
    contained_inside, // new event is inside existing event
    contained_outside, // old event is at least fully covered by new event
    cuts_start, // new event cuts beginning of existing event

};
 
Intersect is_intersect (int l_start, int l_end, int r_start, int r_end);

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
        if (Clockbase::loop_pivot)  {
            curr_event = {}; 
            event_active = false;
        }
        if (!curr_event.has_value())  {
            if (Clockbase::loop_pivot) {
                auto idx = find_active_event(val,events);
                if (idx != -1) {
                    curr_event = events[idx];
                    event_index = val - events[idx].start_time;
                    event_active = true;
                }
            } else {
                auto idx = find_start_event(val, events);
                if (idx != -1) {
                    printf("idx active event: %d\n", idx);
                    curr_event = events[idx];
                    event_active = true;
                } else {
                    return out;
                }
            }
        }
        if (val == curr_event.value().end_time) {
            event_active = false;
            event_index = 0;
            curr_event = {};
        }
        if (event_active) {
            try {
                out = curr_event.value().Out(event_index);
            }
            catch (const std::exception&) {
                printf("here\n");
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
    event_map                                       e_map           {};
    uint32_t                                        event_index     {};
    bool                                            event_active    {};
    
};
 
