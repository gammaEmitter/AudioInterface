//
#pragma once
#include <iostream>
#include <algorithm>
#include "wavetable.h"
#include "iodef.h"
class WaveTableOscillator : public ISignalSource {
public:
    explicit WaveTableOscillator(WaveTableStrategy waveform,  float frequency) : m_frequency(frequency) {
        m_wavetable = std::make_unique<WaveTable>(waveform, frequency);

    }
    ~WaveTableOscillator()  override = default;
    // copy ctor and assignment disabled because of unique_ptr
    WaveTableOscillator(const WaveTableOscillator& osci) = delete;
    WaveTableOscillator& operator=(const WaveTableOscillator& osci) = delete;

    WaveTableOscillator(WaveTableOscillator&& osci) {
        m_wavetable = std::move(osci.m_wavetable);
        m_frequency = osci.m_frequency;
    }
    WaveTableOscillator& operator=(WaveTableOscillator&& osci) {
        m_wavetable = std::move(osci.m_wavetable);
        m_frequency = osci.m_frequency;
        return *this;
    }

    WaveTableOscillator& setFreq(float freq) {
        m_wavetable->set_freq(freq);
        return *this;
    }

    inline float Out () override {
        return m_wavetable->Out();
    }

private:
    std::unique_ptr<WaveTable> m_wavetable; 
    float m_frequency;
};

