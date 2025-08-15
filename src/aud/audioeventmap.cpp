#include "audioeventmap.h"
#include "audioevent.h"
#include "clockbase.h"
#include "curvetool.h"
#include "insertionsort.h"
#include "iodef.h"
#include "mergesort.h"
#include <algorithm>

void init_audio_event_map(AAllocator &alloc, AudioEventMap *&map) {
  map = (AudioEventMap *)allocate_aa(alloc, sizeof(AudioEventMap));
  map->path.proc = &out_audio_event_map;
  map->size_events = 0;
  map->curr_idx_event = -1;
}

void add_event_audio_event_map(AudioEventMap *map, AudioEvent *evt) {
  if (map->size_events > 0) {
    //
    // TODO: place intersect to event of position AFTER it would be sorted
    for (int index = 0; index < map->size_events; ++index) {
      if (index == -1) {
          printf("add event index == -1\n");
          break;
      }
      Intersect state =
          is_intersect(map->events[index]->start_time, map->events[index]->end_time,
                       evt->start_time, evt->end_time);
      printf("intersect state: %d, start time: %d, end time: %d\n", state, evt->start_time, evt->end_time);
      switch (state) {
      case none:
        break;
      case cuts_end:
        map->events[index]->end_time = evt->start_time - 1;
        map->events[index]->duration = map->events[index]->end_time - map->events[index]->start_time + 1;
        short_fade_out(map->events[index]->fade_out, map->events[index]->duration - 1);
        break;
      case contained_inside: {
        map->events[index]->end_time = evt->start_time - 1;
        short_fade_out(map->events[index]->fade_out, map->events[index]->duration - 1);

        AudioEvent *right_residual = map->events[index];
        right_residual->start_time = evt->end_time + 1;
        right_residual->offset = evt->end_time + 1;
        short_fade_in(right_residual->fade_in, right_residual->duration - 1);
        // event is added, but map_>size_events does not get incremented,
        // becasue it is not overlap-processed (could, doesn't need to)
        map->events[map->size_events] = right_residual;
        break;
      }
      case contained_outside:
        map->events[index] = nullptr;
        map->size_events--;
        index--;
        break;
      case cuts_start:
        map->events[index]->start_time = evt->end_time + 1;
        map->events[index]->duration = map->events[index]->end_time - map->events[index]->start_time + 1;
        short_fade_in(map->events[index]->fade_in, map->events[index]->duration - 1);
        break;
      }
    }
  }
   for (int index = 0; index < evt->duration; ++index) { // TRUE
    if (abs(evt->data[index]) > 1) printf("%s %f\n", __FUNCTION__ ,evt->data[index]);
   }
  map->events[map->size_events] = evt;
  map->size_events++;
  if (map->size_events > 1) {
    insertionSort<AudioEvent*>(map->events, map->size_events);
  }
}

void remove_event_audio_event_map(AudioEventMap* map, AudioEvent* evt) {
  u8 index = 0;
  for (;index < map->size_events; ++index) {
    if (evt == map->events[index]) {
      map->events[index] = nullptr;
    }
  }
  ++index;
  if (map->size_events == index) return;

  for (;index < map->size_events; ++index) {
    map->events[index - 1] = map->events[index];
    map->events[index] = nullptr;
  }
  map->size_events -= 1;
}

void remove_event_audio_event_map(AudioEventMap* map, u8 index) {
  if (map->size_events <= index) return;
  map->events[index] = nullptr;
  index++;
  for (;index < map->size_events; ++index) {
    map->events[index - 1] = map->events[index];
    map->events[index] = nullptr;
  }
  map->size_events -= 1;

}

