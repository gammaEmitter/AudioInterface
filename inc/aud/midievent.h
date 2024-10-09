#pragma once

#include "clockbase.h"
#include <optional>

class MidiEvent {
public:
    Timestamp_t                     start_time          {};
    Timestamp_t                     end_time            {};
    float                           pitch               {};
    int                             note_num            {};

    MidiEvent(Timestamp_t start,Timestamp_t duration, int note)
        : start_time(start), end_time(start + duration - 1), note_num(note) {
        pitch = 440.0 * pow(2,((note_num - 69.0f))/12.0f);
    };
    MidiEvent(const MidiEvent &) = default;
    MidiEvent(MidiEvent && other) {
        start_time  = other.start_time;
        end_time    = other.end_time;
        note_num    = other.note_num;
        pitch       = other.pitch; 
    }
    MidiEvent &operator=(const MidiEvent &) = default;
    MidiEvent &operator=(MidiEvent &&) = default;
private:
    MidiEvent() = default;
};

using MidiEvent_opt = std::optional<MidiEvent>;

bool MidiEventCompare (const MidiEvent& lhs, const MidiEvent& rhs);
