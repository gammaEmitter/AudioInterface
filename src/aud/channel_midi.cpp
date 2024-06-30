#include "channel_midi.h"
#include "midieventqueue.h"
#include "iodef.h"
#include "midimessaging.h"

ChannelMidi::ChannelMidi() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

ChannelMidi& ChannelMidi::add_source(SampleOut_fn func){
    sources.push_back(func);
    m_ringbuffer->set_source(sources.back());
    return *this;
}

ChannelMidi& ChannelMidi::add_event(const MidiEvent&& evt) {
    event_queue.add_event(std::move(evt)); 
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

ChannelMidi& ChannelMidi::set_midi (IFreqAdjustable* instrument, ADSR* env_gen) {
    event_queue.midi_rec = &midi_recv;
    midi_listen = MidiListener(*event_queue.midi_rec, 0);
    midi_recv.Init(instrument, env_gen);

    return *this;
}


