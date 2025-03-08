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
    AudioEvent*                     curr_event      {};
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
    // TODO: optimize for using next events start_time instead of polling every frame
    AudioEventMap* map = (AudioEventMap*) arg;
    float out = AudIO::SampleSilence;
    if (map->size_events == 0)  {
        *map->path.out = out;
        return;
    }
    Timestamp_t curr_time = Clockbase::current_time.load();
    if (Clockbase::loop_pivot)  {
        map->curr_event = nullptr; 
        map->event_active = false;
    }
    if (!map->curr_event)  {
        auto idx = find_active_event(curr_time, map->events, map->size_events);
        if (idx != -1) {
            map->curr_event = map->events[idx];
            map->event_index = curr_time - map->curr_event->start_time;
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
        // if (map->event_index > map->curr_event->end_time - map->curr_event->start_time) {
        // if (map->event_index > map->curr_event->duration - 1) {
        if (curr_time == map->curr_event->start_time + map->curr_event->duration) {
            map->event_active = false;
            map->event_index = 0;
            map->curr_event = nullptr;
            map->left_pos = true;
        }
    }
    if (map->event_active) {
        // try {
            if (map->curr_event->stereo) {
                out = out_audio_event(map->curr_event, map->event_index);
                map->event_index++;
            } else {
                if (map->left_pos) {
                    out = out_audio_event(map->curr_event, map->event_index);

                // printf("left %f\n", out);
                    map->event_index++;
                    map->carry_stereo = out;
                } else {
                    out = map->carry_stereo;
                // printf("right %f\n", out);
                } 
                map->left_pos = !map->left_pos;
            }
        // } catch (const std::out_of_range& e) {
        //     printf("we should not be here (index %d on event len %d): %s\n",
        //            map->event_index, map->curr_event->duration, e.what());
        // }
    }
    // if (out >= 1) printf("%f\n", out);
    // set_clampabs1(out, out);
    *map->path.out = out;
    return;
}
