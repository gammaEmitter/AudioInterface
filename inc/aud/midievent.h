#pragma once

#include "clockbase.h"
#include <optional>

enum NoteType{
    NONE,
    ON,
    OFF,
};
// MidiInstruction is controlling behavior of the Instrument
struct MidiEvent {
    Timestamp_t start_time {};
    NoteType ntype = NONE;
    int note = -1;
    MidiEvent(Timestamp_t time, NoteType type, int note_num) : start_time(time), ntype(type), note(note_num) {}
    MidiEvent() = delete;
};

using MidiEvent_opt = std::optional<MidiEvent*>;

bool MidiEventCompare (const MidiEvent& lhs, const MidiEvent& rhs);

