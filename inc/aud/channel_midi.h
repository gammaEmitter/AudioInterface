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
        float out = AudIO::SampleSilence;
        float curr_pitch = event_map.Out_pitch();
        // careful on float comparison!
        if (curr_pitch >= 0) {
            instrument->set_freq(curr_pitch); 
            out += instrument->Out();
        }
        return out;
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




