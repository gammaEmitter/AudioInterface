#pragma once
//
#include <queue>
#include "ringbuffer.h"
#include "iodef.h"
#include "audioevent.h"

class Channel  {
public:
    
    Channel();
    ~Channel() = default;

    ISignalSource* add_source(std::unique_ptr<ISignalSource> src);
    inline float Out() {
        return m_ringbuffer->pull() * m_gain;
    }
    Channel& set_gain (float gain);

    ISignalSource* operator[](size_t index) {
        return sources[index].get();
    }


    std::unique_ptr<Ringbuffer> m_ringbuffer = nullptr;

private:

    std::priority_queue<AudioEvent, std::vector<AudioEvent>, AudioEventCompare> events {};
    std::vector<std::unique_ptr<ISignalSource>> sources {}; 
    float m_gain = 0.3f;


};




