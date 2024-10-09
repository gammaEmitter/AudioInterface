#include "oscillator.h"
#include <mutex>

SineOscillator::SineOscillator(float freq) :
        m_phase(0),
        m_gain(0.71), 
        m_frequencyNorm(freq/AudIO::Samplerate44100), 
        m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    out_fn = std::bind(&SineOscillator::Out, *this);
}

void SineOscillator::set_freq(float freq) {
    m_frequencyNorm = freq/AudIO::Samplerate44100;
    m_phaseIncr = m_frequencyNorm * AudIO::twoPI;
}

void SineOscillator::set_gain(float gain) {
    if (gain >= 1.f) {
        m_gain = 1.f;
    } else if (gain <= 0){
        m_gain = 0.f;
    } else {
        m_gain = gain;
    }
}

SawOscillator::SawOscillator (float freq) : 
    m_phase(0),
    m_gain(0.71), 
    m_frequencyNorm(freq/AudIO::Samplerate44100), 
    m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    out_fn = std::bind(&SawOscillator::Out, *this);
}

void SawOscillator::set_freq(float freq) {
    m_frequencyNorm = freq/AudIO::Samplerate44100;
    m_phaseIncr = m_frequencyNorm * AudIO::twoPI;
}

void SawOscillator::set_gain(float gain) {
    if (gain >= 1.f) {
        m_gain = 1.f;
    } else if (gain <= 0){
        m_gain = 0.f;
    } else {
        m_gain = gain;
    }
}
