#include "midievent.h"

MidiEvent* midi_event(AAllocator& alloc, Timestamp_t start, NoteType type, int note) {

        MidiEvent* event = (MidiEvent*) allocate_aa(alloc, sizeof(MidiEvent));
        event->start_time = start;
        event->ntype = type;
        event->note = note;

        return event;

}

