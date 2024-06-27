#include "channel.h"
#include "audioeventqueue.h"
#include "iodef.h"

Channel::Channel() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

Channel& Channel::add_source(SampleOut func){
    sources.push_back(func);
    m_ringbuffer->set_source(sources.back());
    return *this;
}

Channel& Channel::add_event(const AudioEvent&& evt) {
    event_queue.add_event(std::move(evt)); 
    return *this;
}

Channel& Channel::set_gain (float gain) {
    if (gain > 1.0f) {
        m_gain = 1.0f;
    } else if (gain < -1.0f)  {
        m_gain = -1.0f;
    } else {
        m_gain = gain;
    }
    return *this; 
}
