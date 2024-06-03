#include "channel.h"
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
    events.push(std::move(evt)); 
    if (events.size() == 1) {
        nextEvent = events.top();
    } 
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
