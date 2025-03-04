#include "midieventmap.h"
#include "iodef.h"
#include "midievent.h"

void add_event_midi_event_map(MidiEventMap* map, MidiEvent* evt){
   map->events.emplace_back(evt); 
   std::sort(map->events.begin(), map->events.end(), MidiEventCompare);
}

void init_midi_event_map(AAllocator& alloc, MidiEventMap*& map, OscFreq* recv_freq, ADSR* recv_note) {
   map = (MidiEventMap*) allocate_aa(alloc, sizeof(MidiEventMap));
   map->events = std::vector<MidiEvent*> {};
   map->path.proc = &out_midi_eventmap;
   map->recv_freq = recv_freq;
   map->recv_note = recv_note;
   map->events.reserve(64);
}

void generator_set_midi_event_map (MidiEventMap*& map, SignalPath* generator_path, bool stereo) {
   map->generator_path = generator_path;
   map->stereo_gen = stereo;
}
