#pragma once

#include "clockbase.h"
#include "midievent.h"
#include "midimessaging.h"
#include "iodef.h"
#include <exception>
#include <mutex>


class MidiEventQueue : public Messagable {
public:
    using event_q = std::priority_queue<MidiEvent, std::vector<MidiEvent>, MidiEventCompare>;
    MidiEventQueue(Messagable& midi_receiver);
    MidiEventQueue(const MidiEventQueue &) = default;
    MidiEventQueue(MidiEventQueue &&) = default;
    MidiEventQueue& operator=(const MidiEventQueue &) = default;
    MidiEventQueue& operator=(MidiEventQueue &&) = default;

    inline float Out() {
        float out = AudIO::SampleSilence;
        if (!next_event.has_value()) return out;
        auto val = Clockbase::current_time.load();
        if (val == next_event.value().start_time) {
            this->send(*midi_rec, next_event.value().event_type + " " + std::to_string(next_event.value().note_num), Message::Execution::Immediate);

        }
        return out;

    }

    void add_event (const MidiEvent&& evt);

    MidiEvent_opt                                   next_event      {};
    Messagable*                                     midi_rec        = nullptr;
private:
    event_q                                         queue           {};
    uint32_t                                        event_index     {};
};
