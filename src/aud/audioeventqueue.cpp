#include "audioeventqueue.h"
#include "audioevent.h"
#include "clockbase.h"
#include <__algorithm/ranges_transform.h>
#include <algorithm>


void AudioEventMap::add_event (const AudioEvent&& evt) {
    // if in range evt.start_time + evt.start_time + evt.duration
    // there is (THERE ARE MULTIPLE?) other events, override and adjust duration
    // of the OTHER events. this new event will fully covered

    /* baseline: no two events do Intersect << they will get cut (and need fade to avoid clipping)
     *  find all intersecting events
     *  delete contained events.
     *  -> adjust [end] if old.end > new.start && is intersecting
     *  -> adjust [start] if old.start < new.end && is intersecting
     *  -> cut old into two events if new is contained in old 
     *
     * */
    int num_events = events.size();
    std::vector<Intersect> overlaps (num_events); 
    for (int i = 0; i < num_events; ++i) {
        overlaps[i] = is_intersect(events[i].start_time, events[i].end_time, evt.start_time, evt.end_time);
    }

    events.emplace_back(std::move(evt)); 
    std::sort(events.begin(), events.end(), AudioEventCompare);
}

int find_start_event(Timestamp_t time, const std::vector<AudioEvent>& events){
   int left = 0;
   int right = events.size();
   if (time > events[right - 1].start_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if (events[mid].start_time == time) return mid;
      if (time < events[mid].start_time) {
         right = mid - 1; 
      } else if (time > events[mid].start_time) {
         left = mid + 1; 
      }
   }
   return -1;
}

// binary search on AudioEvent interval from some Timestamp_t
// find event in whiches duration interval the Timestamp_t lies
int find_active_event (Timestamp_t time, const std::vector<AudioEvent>& events) {
   int left = 0;
   int right = events.size();
   if (time > events[right - 1].end_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if (events[mid].start_time <= time && time <= events[mid].end_time) return mid;
      if (time < events[mid].start_time) {
         right = mid - 1; 
      } else if (time > events[mid].end_time) {
         left = mid + 1; 
      }
   }
   return -1;
}

Intersect is_intersect (int l_start, int l_end, int r_start, int r_end) {

        if (l_start >= r_start && l_end <= r_end) {
            return contained_outside;
        }
        if (l_start < r_start && l_end <= r_end) {
            return cuts_end;
        }
        if (l_start >= r_start && l_end > r_end) {
            return cuts_start;
        }
        if (l_start < r_start && l_end > r_end) {
            return contained_inside;
        }
    return none;
}
