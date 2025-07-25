#pragma once

#include "audioevent.h"
#include "clockbase.h"
#include "allocator.h"
#include "iodef.h"
#include <exception>
#include <mutex>
#include <stdexcept>


struct AudioEventMap {
    SignalPath                      path            {};
    i16                             curr_idx_event  {};
    AudioEvent*                     events[64]      {};
    u8                              size_events     {};
    u32                             event_index     {};
    float                           carry_stereo    {};
    bool                            event_active    {};
    bool                            left_pos        {};
     
};


void init_audio_event_map(AAllocator& alloc, AudioEventMap*& map);
void add_event_audio_event_map(AudioEventMap* map, AudioEvent* evt);
 
inline void out_audio_event_map(void* arg) {
    AudioEventMap* map = (AudioEventMap*) arg;
    float out = AudIO::SampleSilence;
    if (map->size_events == 0)  {
        *map->path.out = out;
        return;
    }
    Timestamp_t curr_time = Clockbase::current_time.load();
    if (Clockbase::loop_pivot)  {
        map->curr_idx_event = -1; 
        map->event_active = false;
        map->event_index = 0;
    }
    if (!map->event_active && map->curr_idx_event > -1) {
        if (curr_time == map->events[map->curr_idx_event]->start_time) {
            map->event_active = true;
        } else {
            *map->path.out = out;
            return;
        }
    }
    if (0 > map->curr_idx_event)  {
        map->curr_idx_event = find_active_event(curr_time, map->events, map->size_events);
        // TODO: Handle special cases BeforeFirst and AfterLast
        if (-1 < map->curr_idx_event) {
            map->event_index = curr_time - map->events[map->curr_idx_event]->start_time + map->events[map->curr_idx_event]->offset;
            if ((map->event_index & 1) == 0) {
                map->left_pos =  false;
            } else {
                map->left_pos =  true;
            }
            map->event_active = true;
        } else {
            *map->path.out = out;
            return;
        }
    } else {
        // if (map->event_index > map->curr_idx_event->end_time - map->curr_idx_event->start_time) {
        if (map->event_index > map->events[map->curr_idx_event]->duration - 1) {
        // if (curr_time == map->curr_idx_event->start_time + map->curr_idx_event->duration) {
            map->event_index = 0;
            if (map->curr_idx_event < map->size_events - 1) {
                map->curr_idx_event++;
            } else {
                map->curr_idx_event = -1;
            }
            map->event_active = false;
            map->left_pos = true;
        }
    }
    if (map->event_active) {
        try {
            if (map->events[map->curr_idx_event]->stereo) {
                out = out_audio_event(map->events[map->curr_idx_event], map->event_index);
                map->event_index++;
            } else {
                if (map->left_pos) {
                    out = out_audio_event(map->events[map->curr_idx_event], map->event_index);

                // printf("left %f\n", out);
                    map->event_index++;
                    map->carry_stereo = out;
                } else {
                    out = map->carry_stereo;
                // printf("right %f\n", out);
                } 
                map->left_pos = !map->left_pos;
            }
        } catch (const std::out_of_range& e) {
            printf("we should not be here (index %d on event len %d): %s\n",
                   map->event_index, map->events[map->curr_idx_event]->duration, e.what());
        }
    }
    // if (out >= 1) printf("%f\n", out);
    // set_clampabs1(out, out);
    *map->path.out = out;
    return;
}
