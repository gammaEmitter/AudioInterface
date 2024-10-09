#include "oscillator.h"

SineOscillator::SineOscillator(float freq) :
        adsr(ADSR()),
        m_phase(0),
        m_gain(0.71), 
        m_frequencyNorm(freq/AudIO::Samplerate44100), 
        m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    out_fn = [this](){return Out();};
}

void SineOscillator::send_midi(int type, int note) {
    if (type == 1) {
        set_freq(440.0 * pow(2,((note - 69.0f))/12.0f));
        adsr.state.store(ADSR::State::Attack);
    } else if (type == 2) {
        ADSR::State state = adsr.state.load();
        if (state == ADSR::State::Off || state == ADSR::State::Release) return;
        adsr.fade_into(ADSR::State::Release); 
    }
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
    adsr(ADSR()),
    m_phase(0),
    m_gain(0.71), 
    m_frequencyNorm(freq/AudIO::Samplerate44100), 
    m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    out_fn = [this](){return Out();};
    
}

void SawOscillator::send_midi(int type, int note) {
    if (type == 1) {
        set_freq(440.0 * pow(2,((note - 69.0f))/12.0f));
        adsr.state.store(ADSR::State::Attack);
    } else if (type == 2) {
        ADSR::State state = adsr.state.load();
        if (state == ADSR::State::Off || state == ADSR::State::Release) return;
        adsr.fade_into(ADSR::State::Release); 
    }
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
