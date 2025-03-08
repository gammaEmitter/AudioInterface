#include "audioeventmap.h"
#include "audioevent.h"
#include "clockbase.h"
#include "curvetool.h"
#include "iodef.h"
#include "mergesort.h"
#include <algorithm>

void init_audio_event_map(AAllocator &alloc, AudioEventMap *&map) {
  map = (AudioEventMap *)allocate_aa(alloc, sizeof(AudioEventMap));
  map->path.proc = &out_audio_event_map;
  map->size_events = 0;
  map->curr_event = nullptr;
}

void add_event_audio_event_map(AudioEventMap *map, AudioEvent *evt) {
  if (map->size_events > 0) {
    for (int i = find_active_event(evt->start_time, map->events, map->size_events);
         i < map->size_events; ++i) {
      if (i == -1)
        break;
      Intersect state =
          is_intersect(map->events[i]->start_time, map->events[i]->end_time,
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

        AudioEvent *right_residual = map->events[i];
        right_residual->start_time = evt->end_time + 1;
        right_residual->offset = evt->end_time + 1;
        short_fade_in(right_residual->fade_in, right_residual->duration - 1);
        // event is added, but map_>size_events does not get incremented,
        // becasue it is not overlap-processed (could, doesn't need to)
        map->events[map->size_events] = right_residual;
        break;
      }
      case contained_outside:
        map->events[i] = nullptr;
        map->size_events--;
        i--;
        break;
      case cuts_start:
        map->events[i]->start_time = evt->end_time + 1;
        short_fade_in(map->events[i]->fade_in, map->events[i]->duration - 1);
        break;
      }
    }
  }
   for (int i = 0; i < evt->duration; ++i) { // TRUE
    if (abs(evt->data[i]) > 1) printf("%s %f\n", __FUNCTION__ ,evt->data[i]);
   }
  map->events[map->size_events] = evt;
  map->size_events++;
  // mergeSort(map->events, 0, map->size_events);
}
