#include "midieventmap.h"
#include "iodef.h"
#include "midievent.h"


void MidiEventMap::add_event(const MidiEvent&& evt) {
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
                    break;
                case contained_inside: {
                    events[i].end_time = evt.start_time - 1;

                    MidiEvent right_residual = events[i];
                    right_residual.start_time = evt.end_time + 1;
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
                    break;
            }
        }
   }
   events.emplace_back(std::move(evt)); 
   std::sort(events.begin(), events.end(), MidiEventCompare);
}
