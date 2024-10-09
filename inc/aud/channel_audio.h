#pragma once
//
#include <queue>
#include "clockbase.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "audioevent.h"
#include "audioeventmap.h"


class ChannelAudio : public IChannel {
public:
    
    ChannelAudio();
    ChannelAudio(const ChannelAudio &) = delete;
    ChannelAudio(ChannelAudio &&) = delete;
    ChannelAudio &operator=(const ChannelAudio &) = delete;
    ChannelAudio &operator=(ChannelAudio &&) = delete;
    ~ChannelAudio() = default;

    inline float Out() override {
        // ringbuffer->pull() ist gerade komplett draussen -> redesign auf processing devices
        // float out = AudIO::SampleSilence;
        return event_m.Out();
    }
    ChannelAudio& set_gain (float gain);
    ChannelAudio& add_source(SampleOut_fn func) override;
    ChannelAudio& add_event(const AudioEvent&& evt);

    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    AudioEventMap                                   event_m         {};
    std::vector<SampleOut_fn>                       sources         {};
    float                                           m_gain          = 0.3f;


};




