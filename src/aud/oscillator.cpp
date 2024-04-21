#include "oscillator.h"

SineOscillator::SineOscillator(float freq) :
        m_phase(0),
        m_gain(0.71), 
        m_frequencyNorm(freq/AudIO::Samplerate44100), 
        m_phaseIncr(m_frequencyNorm*AudIO::twoPI) { }

void SineOscillator::setFreq(float freq) {
        m_frequencyNorm = freq/AudIO::Samplerate44100;
        m_phaseIncr = m_frequencyNorm * AudIO::twoPI;
}

void SineOscillator::setGain(float gain) {
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
}
