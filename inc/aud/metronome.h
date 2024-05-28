#pragma once

#include <string>
#include "clockbase.h"
#include "wavtool.h"
#include "iodef.h"
#include <iostream>

class Metronome final : public ISignalSource {
public:
    
    Metronome() : file_name("tock.wav") {
        wav = WavTool::readWAV(file_name);
    }

    void on();
    void off();

    inline float Out() override {
        float out {};
        auto val = Clockbase::current_time.load();
        
        if (index == wav.data.size() - 1) {
            is_playing = false;
            index = 0;
        } else if (val % (Clockbase::beat_length() - AudIO::RingbufferSize) == 0) {
            is_playing = true;
        }
        if (is_playing) {
            out = wav.data[index];
            index++;
        } else {
            out = AudIO::SampleSilence;
        }
        return out;

    }

private:
    std::string                 file_name   {};
    size_t                      index       {};
    bool                        is_playing   = false;
    WavTool::RiffWAV            wav;
    static constexpr size_t     metro_size = 22364;

    void loadFile();
};
