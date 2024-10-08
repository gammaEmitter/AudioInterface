#include "audioeventqueue.h"
#include "audioevent.h"
#include "clockbase.h"
#include "curvetool.h"
#include <algorithm>


void AudioEventMap::add_event (const AudioEvent&& evt) {
    int num_events = events.size();
    if (num_events > 0) {
        for (int i = find_active_event(evt.start_time, events); i < num_events; ++i) {
            if (i == -1) break;
            Intersect state = is_intersect(events[i].start_time, events[i].end_time, 
                                           evt.start_time, evt.end_time);
            switch (state) {
                case none:
                    break;
                case cuts_end:
                    events[i].end_time = evt.start_time - 1;
                    short_fade_out(events[i].fade_out, events[i].duration - 1);
                    break;
                case contained_inside: {
                    events[i].end_time = evt.start_time - 1;
                    short_fade_out(events[i].fade_out, events[i].duration - 1);

                    AudioEvent right_residual = events[i];
                    right_residual.start_time = evt.end_time + 1;
                    right_residual.offset = evt.end_time + 1;
                    short_fade_in(right_residual.fade_in, right_residual.duration - 1);
                    // event is added, but num_events does not get incremented,
                    // becasue it is not overlap-processed (could, doesn't need to)
                    events.emplace_back(std::move(right_residual));
                    break;
                }
                case contained_outside:
                    events.erase(events.begin() + i);
                    num_events--;
                    i--;
                    break;
                case cuts_start:
                    events[i].start_time = evt.end_time + 1;
                    short_fade_in(events[i].fade_in, events[i].duration - 1);
                    break;
            }
        }
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

Intersect is_intersect (int old_start, int old_end, int new_start, int new_end) {
        if (old_start >= new_start && old_end <= new_end) {
            return contained_outside;
        }
        if (old_start < new_start && old_end < new_end && old_end > new_start) {
            return cuts_end;
        }
        if (old_start > new_start && old_end > new_end &&  old_start < new_end) {
            return cuts_start;
        }
        if (old_start < new_start && old_end > new_end) {
            return contained_inside;
        }
    return none;
}
