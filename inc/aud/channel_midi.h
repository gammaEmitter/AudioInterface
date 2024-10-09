#pragma once
//
#include <queue>
#include "clockbase.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "midievent.h"
#include "midieventmap.h"



class ChannelMidi : public IChannel {
public:
    
    ChannelMidi();
    ChannelMidi(const ChannelMidi &) = delete;
    ChannelMidi(ChannelMidi &&) = delete;
    ChannelMidi &operator=(const ChannelMidi &) = delete;
    ChannelMidi &operator=(ChannelMidi &&) = delete;
    ~ChannelMidi() = default;

    inline float Out() override {
        // TODO: click at loop_pivot --> cannot(?) place fade-out on midi.clip
        MidiEvent* evt = event_map.Out_midi();
        if (evt) {
            instrument->send_midi((int) evt->ntype, evt->note); 
        }
        return instrument->Out();
    }
    ChannelMidi& set_gain (float gain);
    ChannelMidi& add_source(SampleOut_fn func) override;
    ChannelMidi& set_instrument(IInstrument* func);
    ChannelMidi& add_event(const MidiEvent&& evt);


    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    MidiEventMap                                    event_map       {};
    std::vector<SampleOut_fn>                       effects         {};
    IInstrument*                                    instrument      {};
    SampleOut_fn                                    source          {};
    float                                           m_gain          = 0.3f;


};




