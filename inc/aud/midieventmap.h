#pragma once

#include "clockbase.h"
#include "midievent.h"
#include "iodef.h"
#include <exception>
#include <optional>


class MidiEventMap{
public:
    MidiEventMap() {};
    MidiEventMap(const MidiEventMap &) = default;
    MidiEventMap(MidiEventMap &&) = default;
    MidiEventMap& operator=(const MidiEventMap &) = default;
    MidiEventMap& operator=(MidiEventMap &&) = default;

    inline MidiEvent* Out_midi() {
        MidiEvent* evt = nullptr;
        Timestamp_t curr_time = Clockbase::current_time.load();
        auto idx = find_start_event(curr_time, events);
        if (idx != -1) {
            evt = &events[idx];
        }
        return evt;
    }

    void add_event (const MidiEvent&& evt);

private:
    std::vector<MidiEvent>                          events          {};
};
