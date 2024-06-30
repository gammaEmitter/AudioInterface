//
#pragma once
#include "channel_audio.h"
#include "channel_midi.h"
#include "iodef.h"
#include <memory>
class Bus {
public:

    Bus() = default;
    ~Bus() = default;
    Bus(const Bus& other) = delete;
    Bus& operator=(const Bus& other) = delete;

    Bus(Bus&& other) {
        for (auto& ch_ptr : other.sources) {
            sources.emplace_back(std::move(ch_ptr));
        }
    }
    Bus& operator=(Bus&& other) {
        for (auto& ch_ptr : other.sources) {
            sources.emplace_back(std::move(ch_ptr));
        }
        return *this;
    }
    IChannel* channel(size_t index) {
        return sources[index].get();
    }
    ChannelMidi* add_channel_midi();
    ChannelAudio* add_channel_audio();
    float Out();
private:
    std::vector<std::unique_ptr<IChannel>> sources      {};
};

class MasterBus : public Bus {
public:
    MasterBus() {
    };

private:
};





