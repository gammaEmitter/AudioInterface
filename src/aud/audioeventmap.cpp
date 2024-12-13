#include "audioeventmap.h"
#include "audioevent.h"
#include "clockbase.h"
#include "curvetool.h"
#include "iodef.h"
#include <algorithm>

using std::move;

AudioEventMap *init_audio_event_map(AAllocator &alloc) {
  AudioEventMap *aem =
      (AudioEventMap *)allocate_aa(alloc, sizeof(AudioEventMap));
  aem->path.proc = &out_audio_event_map;
  return aem;
}

void add_event_audio_event_map(AudioEventMap* map, AudioEvent* evt) {
    int num_events = map->events.size();
    if (num_events > 0) {
        for (int i = find_active_event(evt->start_time, map->events); i < num_events; ++i) {
            if (i == -1) break;
            Intersect state = is_intersect(map->events[i]->start_time, map->events[i]->end_time, 
                                           evt->start_time, evt->end_time);
            switch (state) {
                case none:
                    break;
                case cuts_end:
                    map->events[i]->end_time = evt->start_time - 1;
                    short_fade_out(map->events[i]->fade_out, map->events[i]->duration - 1);
                    break;
                case contained_inside: {
                    map->events[i]->end_time = evt->start_time - 1;
                    short_fade_out(map->events[i]->fade_out, map->events[i]->duration - 1);

                    AudioEvent* right_residual = map->events[i];
                    right_residual->start_time = evt->end_time + 1;
                    right_residual->offset = evt->end_time + 1;
                    short_fade_in(right_residual->fade_in, right_residual->duration - 1);
                    // event is added, but num_events does not get incremented,
                    // becasue it is not overlap-processed (could, doesn't need to)
                    map->events.emplace_back(std::move(right_residual));
                    break;
                }
                case contained_outside:
                    map->events.erase(map->events.begin() + i);
                    num_events--;
                    i--;
                    break;
                case cuts_start:
                    map->events[i]->start_time = evt->end_time + 1;
                    short_fade_in(map->events[i]->fade_in, map->events[i]->duration - 1);
                    break;
            }
        }
    }
    // TODO:
    map->events.push_back(evt); 
    std::sort(map->events.begin(), map->events.end(), AudioEventCompare);
}

