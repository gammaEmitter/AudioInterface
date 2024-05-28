#include "channel.h"
#include "iodef.h"

Channel::Channel() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

ISignalSource* Channel::add_source(std::unique_ptr<ISignalSource> src){

    sources.push_back(std::move(src));
    auto tmp = std::bind(&ISignalSource::Out,sources.back().get());    
    m_ringbuffer->set_source(tmp);
    return sources.back().get();
}

Channel& Channel::add_event(const AudioEvent evt) {
    events.push(evt); 
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
