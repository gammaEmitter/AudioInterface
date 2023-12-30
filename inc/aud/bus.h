//
#pragma once
#include "channel.h"
#include "iodef.h"
#include "bufferservice.h"
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
    Channel* add_channel();
    std::vector<Channel*> channels();
    float Out();
private:
    std::vector<std::unique_ptr<Channel>> sources;
};

class MasterBus : public Bus {
public:
    MasterBus() {
    };

private:
};





