#pragma once

#include <string>
#include "clockbase.h"
#include "wavtool.h"
#include "iodef.h"
#include <iostream>

struct Metronome {
    Metronome() : file_name("res/tock.wav") {
    }

    void on();
    void off();

    std::string                 file_name   {};
    size_t                      index       {};
    bool                        is_playing   = false;
    WavTool::RiffWAV*           wav;

    void loadFile();
};

inline float out_metronome(Metronome& metr) {
        float out {};
        auto val = Clockbase::current_time.load();
        
        if (metr.index == metr.wav->len_data - 1) {
            metr.is_playing = false;
            metr.index = 0;
        } else if (val % (Clockbase::beat_length()) == 0) {
            metr.is_playing = true;
        }
        if (metr.is_playing) {
            out = metr.wav->data[metr.index];
            metr.index++;
        } else {
            out = AudIO::SampleSilence;
        }
        return out;
}

void init_metronome (Metronome& metr);
