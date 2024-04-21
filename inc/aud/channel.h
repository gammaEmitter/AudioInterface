#pragma once
//
#include "ringbuffer.h"
#include "iodef.h"
class Channel  {
public:

    Channel();
    ~Channel() = default;

    ISignalSource* add_source(std::unique_ptr<ISignalSource> src);
    inline float Out() {
        return m_ringbuffer->pull() * m_gain;
    }
    Channel& set_gain (float gain);

private:
    std::unique_ptr<Ringbuffer> m_ringbuffer = nullptr;
    std::vector<std::unique_ptr<ISignalSource>> sources {}; 
    float m_gain = 0.3f;


};




