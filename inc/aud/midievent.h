#pragma once

#include "clockbase.h"
#include "allocator.h"
#include <optional>

enum NoteType{
    NONE,
    ON,
    OFF,
};
struct MidiEvent {
    Timestamp_t start_time {};
    NoteType ntype = NONE;
    int note = -1;
};
MidiEvent* midi_event(AAllocator& alloc, Timestamp_t start, NoteType type, int note);

inline float note_to_hz(int note, float hz_base) {
    return hz_base * pow(2,((note - 69.0f))/12.0f) ;
}


bool MidiEventCompare (const MidiEvent* lhs, const MidiEvent* rhs);

