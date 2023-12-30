

#include "iodef.h"

class SineOscillator : public ISignalSource {
public:
    SineOscillator (float freq) : 
        m_phase(0),
        m_gain(0.71), 
        m_frequencyNorm(freq/AudIO::Samplerate44100), 
        m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    }
    void setFreq(float freq) {
        m_frequencyNorm = freq/AudIO::Samplerate44100;
        m_phaseIncr = m_frequencyNorm * AudIO::twoPI;
    }
    void setGain(float gain) {
        if (gain >= 1.f) {
            m_gain = 1.f;
        } else if (gain <= 0){
            m_gain = 0.f;
        } else {
            m_gain = gain;
        }
    }
    inline float Out() override {
        float sample =sin(m_phase); 
        m_phase += m_phaseIncr;
        m_phase = (m_phase >= AudIO::twoPI) ? (m_phase - AudIO::twoPI) : m_phase;
        return sample * m_gain;
    }
private:
    float m_phase {};
    float m_gain {};
    float m_frequencyNorm {}; 
    float m_phaseIncr {};
};
class SawOscillator : public ISignalSource {
public:
    SawOscillator (float freq) : 
        m_phase(0),
        m_gain(0.71), 
        m_frequencyNorm(freq/AudIO::Samplerate44100), 
        m_phaseIncr(m_frequencyNorm*AudIO::twoPI) {
    }
    void setFreq(float freq) {
        m_frequencyNorm = freq/AudIO::Samplerate44100;
        m_phaseIncr = m_frequencyNorm * AudIO::twoPI;
    }
    void setGain(float gain) {
        if (gain >= 1.f) {
            m_gain = 1.f;
        } else if (gain <= 0){
            m_gain = 0.f;
        } else {
            m_gain = gain;
        }
    }
    inline float Out() override {
        float dt = m_phase / AudIO::twoPI;
        float sample = ((2.f*dt) - 1.f) ; 
        float polyBLEP = 0.f;
        if (dt < m_frequencyNorm) {
            dt /= m_frequencyNorm;
            polyBLEP = 2*dt - dt*dt - 1.f;
        } else if (dt > 1.f - m_frequencyNorm) {
            dt = (dt - 1.f) / m_frequencyNorm;
            polyBLEP = 2*dt + dt*dt  + 1.f; 
        }
        sample -= polyBLEP;
        m_phase += m_phaseIncr;
        m_phase = (m_phase >= AudIO::twoPI) ? (m_phase - AudIO::twoPI) : m_phase;
        return sample * m_gain;
    }
private:
    float m_phase {};
    float m_gain {};
    float m_frequencyNorm {}; 
    float m_phaseIncr {};
};
