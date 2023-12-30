#pragma once
//
#include "ringbuffer.h"
#include "iodef.h"
#include "wtoscillator.h"
#include "oscillator.h"
class Channel  {
public:

    Channel();
    ~Channel() = default;

    void add_source(std::unique_ptr<ISignalSource> src);
    float Out();

private:
    std::unique_ptr<Ringbuffer> m_ringbuffer = nullptr;
    std::vector<std::unique_ptr<ISignalSource>> sources {}; 
    float m_gain = 0.3f;


};




