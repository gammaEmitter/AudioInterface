#include "iodef.h"

class SineOscillator : public ISignalSource, public IFreqAdjustable {
public:
    SineOscillator (float freq);
    void setFreq(float freq) override;
    void setGain(float gain);
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
class SawOscillator : public ISignalSource, public IFreqAdjustable {
public:
    SawOscillator (float freq);
    void setFreq(float freq) override;
    void setGain(float gain);
    inline float Out() override {
        float dt = m_phase / AudIO::twoPI;
        float sample = ((2.f*dt) - 1.f); 
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
