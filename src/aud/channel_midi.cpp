#include "channel_midi.h"
#include "midieventmap.h"
#include "iodef.h"

ChannelMidi::ChannelMidi() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

ChannelMidi& ChannelMidi::add_source(SampleOut_fn func){
    effects.push_back(func);
    return *this;
}

ChannelMidi& ChannelMidi::set_instrument(IInstrument* instr){
    instrument = instr;
    source = instrument->out_fn;
    m_ringbuffer->set_source(source);
    return *this;
}

ChannelMidi& ChannelMidi::add_event(const MidiEvent&& evt) {
    event_map.add_event(std::move(evt)); 
    return *this;
}

ChannelMidi& ChannelMidi::set_gain (float gain) {
    if (gain > 1.0f) {
        m_gain = 1.0f;
    } else if (gain < -1.0f)  {
        m_gain = -1.0f;
    } else {
        m_gain = gain;
    }
    return *this; 
}


