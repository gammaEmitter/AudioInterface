#pragma once
//
#include <queue>
#include "clockbase.h"
#include "ringbuffer.h"
#include "iodef.h"
#include "audioevent.h"

using AudioEventQueue = std::priority_queue<AudioEvent, std::vector<AudioEvent>, AudioEventCompare>;

class Channel  {
public:
    
    Channel();
    Channel(const Channel &) = delete;
    Channel(Channel &&) = delete;
    Channel &operator=(const Channel &) = delete;
    Channel &operator=(Channel &&) = delete;
    ~Channel() = default;

    inline float Out() {
        if (!nextEvent.has_value()) {
            return m_ringbuffer->pull();
        }
        float out {};
        auto val = Clockbase::current_time.load(); 
        if (val == (nextEvent.value().start_time \
                        + nextEvent.value().duration - 1)) {
            event_active = false;
            index = 0;
            events.pop();
            if (events.empty()) {
                nextEvent = {};
            } else {
                nextEvent = events.top();
            }
        } else if (val == nextEvent.value().start_time) {
            event_active = true;
        }
        if (event_active) {
            out = nextEvent.value().data->at(index);
            index++;
        }
        return out;
    }
    Channel& set_gain (float gain);
    ISignalSource* add_source(std::unique_ptr<ISignalSource> src);
    Channel& add_event(const AudioEvent&& evt);

    ISignalSource* operator[](size_t index) {
        return sources[index].get();
    }


    std::unique_ptr<Ringbuffer>                     m_ringbuffer    = nullptr;

private:

    AudioEventQueue                                 events          {};
    AudioEvent_opt                                  nextEvent       {};
    std::vector<std::unique_ptr<ISignalSource>>     sources         {};
    uint32_t                                        index           {};
    bool                                            event_active    {};
    float                                           m_gain          = 0.3f;


};




