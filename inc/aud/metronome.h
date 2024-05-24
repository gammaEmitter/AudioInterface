#pragma once

#include <string>
#include "clockbase.h"
#include "wavtool.h"
#include "iodef.h"
#include <iostream>

class Metronome final : public ISignalSource {
public:
    
    Metronome() : file_name("tock.wav") {
        loadFile();
    }

    void on();
    void off();

    inline float Out() override {
        float out {};
        auto val = Clockbase::samples_passed.load(); 
        if (val == (metro_size / 2) - 1) {
            is_playing = false;
            index = 0;
        } else if (val == 44099 - AudIO::RingbufferSize) {
            is_playing = true;
        }
        if (is_playing) {
            out = audio_data[index];
            index += 2;
        } else {
            out = AudIO::SampleSilence;
        }
        return out;

    }

private:
    std::string                 file_name   {};
    std::vector<float>          audio_data  {};
    size_t                      index       {};
    bool                        is_playing   = false;
    
    static constexpr size_t            metro_size = 26112;

    void loadFile();
};
