#pragma once

#include "audioevent.h"
#include "clockbase.h"
#include "../allocator.h"
#include "iodef.h"
#include <exception>
#include <mutex>
#include <map>


struct AudioEventMap {
    SignalPath                                      path            {};
    AudioEvent*                                     curr_event      {};
    std::vector<AudioEvent*>                        events          {};
    u32                                             event_index     {};
    bool                                            event_active    {};
    
};


AudioEventMap* init_audio_event_map(AAllocator& alloc);
void add_event_audio_event_map(AudioEventMap* map, AudioEvent* evt);
 
inline void out_audio_event_map(void* arg) {
    AudioEventMap* map = (AudioEventMap*) arg;
    float out = AudIO::SampleSilence;
    if (map->events.size() == 0)  {
        printf("no elements\n");
        *map->path.out = out;
        return;
    }
    Timestamp_t curr_time = Clockbase::current_time.load();
    if (Clockbase::loop_pivot)  {
        map->curr_event = nullptr; 
        map->event_active = false;
    }
    if (!map->curr_event)  {
        if (Clockbase::loop_pivot) {
            auto idx = find_active_event(curr_time,map->events);
            if (idx != -1) {
                map->curr_event = map->events[idx];
                map->event_index = curr_time - map->events[idx]->start_time;
                map->event_active = true;
            }
        } else {
            auto idx = find_start_event(curr_time, &map->events);
            if (idx != -1) {
                map->curr_event = map->events[idx];
                map->event_active = true;
            } else {
                *map->path.out = out;
                return;
            }
        }
    } else {
        if (curr_time == map->curr_event->end_time) {
            map->event_active = false;
            map->event_index = 0;
            map->curr_event = nullptr;
        }
    }
    if (map->event_active) {
        try {
            out = out_audio_event(map->curr_event, map->event_index);
        }
        catch (const std::exception&) {
            printf("we should not be here\n");
            exit(1);
        }
        map->event_index++;
    }
    *map->path.out =  out;
    return;
}
