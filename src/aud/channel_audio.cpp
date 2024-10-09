#include "channel_audio.h"
#include "audioeventmap.h"
#include "iodef.h"

ChannelAudio::ChannelAudio() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

ChannelAudio& ChannelAudio::add_source(SampleOut_fn func){
    sources.push_back(func);
    m_ringbuffer->set_source(sources.back());
    return *this;
}

ChannelAudio& ChannelAudio::add_event(const AudioEvent&& evt) {
    event_m.add_event(std::move(evt)); 
    return *this;
}

ChannelAudio& ChannelAudio::set_gain (float gain) {
    if (gain > 1.0f) {
        m_gain = 1.0f;
    } else if (gain < -1.0f)  {
        m_gain = -1.0f;
    } else {
        m_gain = gain;
    }
    return *this; 
}
