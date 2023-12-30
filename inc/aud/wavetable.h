//
#pragma once

#include <memory>
#include "iodef.h"


std::vector<float> SineWaveTableStgy();
std::vector<float> SawWaveTableStgy();
std::vector<float> SquareWaveTableStgy();


class WaveTable {

public:

    WaveTable(WaveTableStrategy waveform, float frequency);
    WaveTable(const WaveTable& wavetbl) = delete;
    WaveTable& operator=(const WaveTable& wavetbl) = delete;

    WaveTable(WaveTable&& wavetbl) {
        m_wt = std::move(wavetbl.m_wt);
        m_index = wavetbl.m_index;
        m_incr = wavetbl.m_incr;
        m_freq = wavetbl.m_freq;
    }
    WaveTable& operator=(WaveTable&& wavetbl) {

        m_wt = std::move(wavetbl.m_wt);
        m_index = wavetbl.m_index;
        m_incr = wavetbl.m_incr;
        m_freq = wavetbl.m_freq;
        return *this;
    }
    float Out();
    size_t size();
    void set_freq(float freq);

private:
    std::vector<float> m_wt;
    float m_freq;
    int m_index = 0;
    int m_incr;



};
