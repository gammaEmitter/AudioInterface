#include "channel.h"
#include "iodef.h"

Channel::Channel() {
    m_ringbuffer = std::make_unique<Ringbuffer>();
}

void Channel::add_source(std::unique_ptr<ISignalSource> src){

    sources.push_back(std::move(src));
    auto tmp = std::bind(&ISignalSource::Out,sources.back().get());    
    m_ringbuffer->set_source(tmp);
}

float Channel::Out()  {
    return m_ringbuffer->pull();
};
