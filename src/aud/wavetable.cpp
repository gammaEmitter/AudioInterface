//
#include "wavetable.h"
#include "iodef.h"
//#include "../inc/audiointerface.h"
#include <cmath>

std::vector<float> SineWaveTableStgy()  {
    std::vector<float> wavetable;
    wavetable.reserve (AudIO::WaveTableSize + 1);
    for (int i = 0; i < AudIO::WaveTableSize - 1; ++i) {
        float phase = static_cast<float>(i) / static_cast<float>(AudIO::WaveTableSize - 1);

        wavetable.emplace_back( std::sin(phase * 2*M_PI));
    }
    wavetable[0] = 0.f;
    wavetable[AudIO::WaveTableSize] = 0.f;
    wavetable.emplace_back(0.0f);
    
    return wavetable;
}
std::vector<float> SawWaveTableStgy()  {
    std::vector<float> wavetable;
    wavetable.reserve (AudIO::WaveTableSize + 1);
    float gain = 0.7f;
    // -2 --> top to bottom saw
    // Start Value = 1
    // End Value = -1
    // Range to fill = abs(Start + End) == 2
    float delta = -2.f*gain / static_cast<float>(AudIO::WaveTableSize - 1);
    for (int i = 0; i < AudIO::WaveTableSize - 1; ++i) {
     wavetable.emplace_back(gain + delta * i);
    }
    wavetable.emplace_back(-gain); // for rollover in loop
    wavetable.emplace_back(gain);
    return wavetable;
}

std::vector<float> SquareWaveTableStgy()  {
    std::vector<float> wavetable;
    wavetable.reserve(AudIO::WaveTableSize + 1);
    float gain = 1.f;
    int halfperiode = AudIO::WaveTableSize / 2;

    for (int i = 0; i < AudIO::WaveTableSize -1; ++i) {
        if (i <= halfperiode) {
            wavetable.emplace_back(gain);
        } else {
            wavetable.emplace_back(-gain);
        }
    } 
    wavetable.emplace_back(-gain);
    wavetable.emplace_back(gain);
    return wavetable;
}

WaveTable::WaveTable(WaveTableStrategy waveform, float frequency) {
    m_wt = waveform();
    m_freq = frequency;
    m_incr = static_cast<int>(std::floor((static_cast<float>(AudIO::WaveTableSize)
                   / AudIO::Samplerate44100) * m_freq));

}

float WaveTable::Out() {
        float tmp = m_wt[m_index];
        m_index = (m_index + m_incr ) % AudIO::WaveTableSize;
        return tmp;
}

void WaveTable::set_freq(float freq) {
    m_freq = freq;
    m_incr = static_cast<int>(std::floor((static_cast<float>(AudIO::WaveTableSize)
                   / AudIO::Samplerate44100) * m_freq));
}

size_t WaveTable::size() {
    return m_wt.size();
}
