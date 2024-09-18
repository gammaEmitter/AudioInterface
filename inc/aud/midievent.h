#pragma once

#include "clockbase.h"
#include "libremidi/message.hpp"
#include <optional>

class MidiEvent {
public:
    Timestamp_t                     start_time          {};
    std::string                     event_type          {};
    float                           pitch               {};
    int                             note_num            {};

    MidiEvent(Timestamp_t start, std::string_view type, int note)
        : start_time(start), event_type(type), note_num(note) {
            pitch = 440.0 * pow(2,((note_num - 69.0f))/12.0f);
    };
    MidiEvent(const MidiEvent &) = default;
    MidiEvent(MidiEvent && other) {
        start_time  = other.start_time;
        event_type  = other.event_type;
        note_num    = other.note_num;
        pitch       = other.pitch; 
    }
    MidiEvent &operator=(const MidiEvent &) = default;
    MidiEvent &operator=(MidiEvent &&) = default;
private:
    MidiEvent() = default;
};

using MidiEvent_opt = std::optional<MidiEvent>;

struct MidiEventCompare {
    bool operator() (const MidiEvent& lhs, const MidiEvent& rhs) {
        return lhs.start_time > rhs.start_time;
    }
};
