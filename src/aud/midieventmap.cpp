#include "midieventmap.h"
#include "iodef.h"
#include "midievent.h"

void MidiEventMap::add_event(const MidiEvent&& evt) {
   events.emplace_back(std::move(evt)); 
   std::sort(events.begin(), events.end(), MidiEventCompare);
}
