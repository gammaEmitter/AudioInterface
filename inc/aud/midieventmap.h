#pragma once

#include "clockbase.h"
#include "midievent.h"
#include "iodef.h"
#include <exception>
#include <optional>


class MidiEventMap{
public:
    MidiEventMap() {};
    MidiEventMap(const MidiEventMap &) = default;
    MidiEventMap(MidiEventMap &&) = default;
    MidiEventMap& operator=(const MidiEventMap &) = default;
    MidiEventMap& operator=(MidiEventMap &&) = default;

    inline int Out_pitch() {
        float out = AudIO::NoNote;
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
                    printf("idx active event: %d\n", idx);
                    curr_event = events[idx];
                    event_active = true;
                } else {
                    return out;
                }
            }
        }
        if (curr_time == curr_event.value().end_time) {
            event_active = false;
            event_index = 0;
            curr_event = {};
        }
        if (event_active) {
            try {
                out = curr_event.value().pitch;
            }
            catch (const std::exception&) {
                printf("here\n");
                exit(1);
            }
            event_index++;
        }
        return out;
    }

    void add_event (const MidiEvent&& evt);

    MidiEvent_opt                                   curr_event      {};
private:
    std::vector<MidiEvent>                          events          {};
    u32                                             event_index     {};
    bool                                            event_active    {};
};
