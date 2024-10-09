//
#pragma once
#include <iostream>
#include <algorithm>
#include "wavetable.h"
#include "iodef.h"
class WaveTableOscillator : public ISignalSource, public IInstrument {
public:
    explicit WaveTableOscillator(WaveTableStrategy_fn waveform,  float frequency);
    ~WaveTableOscillator() override = default;
    // copy ctor and assignment disabled because of unique_ptr
    WaveTableOscillator(WaveTableOscillator& osci) = delete;
    WaveTableOscillator& operator=(WaveTableOscillator& osci) = delete;
    WaveTableOscillator(WaveTableOscillator&& osci) {
        if (&osci == this) return;
        m_wavetable = std::move(osci.m_wavetable);
        m_frequency = osci.m_frequency;
    }
    WaveTableOscillator& operator=(WaveTableOscillator&& osci) {
        if (&osci == this) return *this;
        m_wavetable = std::move(osci.m_wavetable);
        m_frequency = osci.m_frequency;
        return *this;
    }

    SampleOut_fn out_fn = nullptr;

    void set_freq(float freq) override {
        m_wavetable->set_freq(freq);
    }

    inline float Out () override {
        return m_wavetable->Out();
    }

private:
    std::unique_ptr<WaveTable> m_wavetable; 
    float m_frequency;
};

