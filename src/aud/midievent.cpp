#include "midievent.h"

MidiEvent* midi_event(AAllocator& alloc, Timestamp_t start, NoteType type, int note) {

        MidiEvent* event = (MidiEvent*) allocate_aa(alloc, sizeof(MidiEvent));
        event->start_time = start;
        event->ntype = type;
        event->note = note;

        return event;

}
bool MidiEventCompare (const MidiEvent* lhs, const MidiEvent* rhs) {
        return lhs->start_time < rhs->start_time;
};
