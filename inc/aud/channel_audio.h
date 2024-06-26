#pragma once
//
#include <queue>
#include "clockbase.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "audioevent.h"
#include "audioeventqueue.h"


class ChannelAudio : public IChannel {
public:
    
    ChannelAudio();
    ChannelAudio(const ChannelAudio &) = delete;
    ChannelAudio(ChannelAudio &&) = delete;
    ChannelAudio &operator=(const ChannelAudio &) = delete;
    ChannelAudio &operator=(ChannelAudio &&) = delete;
    ~ChannelAudio() = default;

    inline float Out() override {
        if (!event_queue.next_event.has_value()) {
            return m_ringbuffer->pull();
        } else {
            return event_queue.Out();
        }
    }
    ChannelAudio& set_gain (float gain);
    ChannelAudio& add_source(SampleOut_fn func) override;
    ChannelAudio& add_event(const AudioEvent&& evt);


    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    AudioEventQueue                                 event_queue     {};
    std::vector<SampleOut_fn>                       sources         {};
    float                                           m_gain          = 0.3f;


};




