#pragma once
#include "iodef.h"
#include "libremidi/input_configuration.hpp"
#include "libremidi/libremidi.hpp"
#include "libremidi/message.hpp"
#include "midievent.h"
#include "adsr.h"
#include "messagable.h"


namespace MidiNote {
    constexpr int NOTE_RANGE_START = 21;
    constexpr int NOTE_RANGE_END = 108;
}

class MidiReceiver : public Messagable {
public:
    void send_event (const MidiEvent& event);
    MidiReceiver(){};
    void Init(IFreqAdjustable* instrument, ADSR* env_gen);

    IFreqAdjustable*                instrument  = nullptr;
    ADSR*                           adsr        = nullptr;
};


class MidiListener : public Messagable {
public:
    MidiListener(Messagable& midi_receiver, int port_num);
private:
    std::unique_ptr<libremidi::midi_in>     midi_conn       = nullptr;    
};
