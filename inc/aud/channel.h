#pragma once
//
#include <queue>
#include "clockbase.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "audioevent.h"
#include "audioeventqueue.h"


class Channel  {
public:
    
    Channel();
    Channel(const Channel &) = delete;
    Channel(Channel &&) = delete;
    Channel &operator=(const Channel &) = delete;
    Channel &operator=(Channel &&) = delete;
    ~Channel() = default;

    inline float Out() {
        if (!event_queue.next_event.has_value()) {
            return m_ringbuffer->pull();
        } else {
            return event_queue.Out();
        }
    }
    Channel& set_gain (float gain);
    Channel& add_source(SampleOut func);
    Channel& add_event(const AudioEvent&& evt);

    SampleOut* operator[](size_t event_index) {
        return &sources[event_index];
    }


    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    AudioEventQueue                                 event_queue     {};
    std::vector<SampleOut>                          sources         {};
    float                                           m_gain          = 0.3f;


};




