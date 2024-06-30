#pragma once
//
#include <queue>
#include "clockbase.h"
#include "midimessaging.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "midievent.h"
#include "midieventqueue.h"



class ChannelMidi : public IChannel {
public:
    
    ChannelMidi();
    ChannelMidi(const ChannelMidi &) = delete;
    ChannelMidi(ChannelMidi &&) = delete;
    ChannelMidi &operator=(const ChannelMidi &) = delete;
    ChannelMidi &operator=(ChannelMidi &&) = delete;
    ~ChannelMidi() = default;

    inline float Out() override {
        if (!event_queue.next_event.has_value()) {
            return m_ringbuffer->pull();
        } else {
            return event_queue.Out();
        }
    }
    ChannelMidi& set_gain (float gain);
    ChannelMidi& add_source(SampleOut_fn func) override;
    ChannelMidi& add_event(const MidiEvent&& evt);
    ChannelMidi& set_midi (IFreqAdjustable* instrument, ADSR* env_gen);


    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    MidiReceiver                                    midi_recv       {};
    MidiEventQueue                                  event_queue     {midi_recv};
    MidiListener                                    midi_listen     {midi_recv, 0};
    std::vector<SampleOut_fn>                       sources         {};
    float                                           m_gain          = 0.3f;


};




