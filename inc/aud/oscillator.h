#include "adsr.h"
#include "iodef.h"
#include "../allocator.h"


enum WaveType {
    SINE,
    SAW,
    TRIANGLE,
    SQUARE
};

struct Oscillator {
    SignalPath path;
    OscFreq freq;
    //ADSR adsr {};
    float phase {};
    float gain {};
};
inline void out_osc_sine (void* arg){
    Oscillator* osc = (Oscillator*) arg;
    float sample = sin(osc->phase); 
    osc->phase += osc->freq.incr_phase;
    osc->phase = (osc->phase >= AudIO::twoPI) ? (osc->phase - AudIO::twoPI) : osc->phase;
    *osc->path.out = sample * osc->gain; //* out_adsr(osc->adsr);
    if (osc->path.in) *osc->path.out *= *osc->path.in;
}

inline void out_osc_saw(void* arg) {
    Oscillator* osc = (Oscillator*) arg;
    float dt = osc->phase / AudIO::twoPI;
    float sample = ((2.f*dt) - 1.f); 
    float polyBLEP = 0.f;
    if (dt < osc->freq.frequency_norm) {
        dt /= osc->freq.frequency_norm;
        polyBLEP = 2*dt - dt*dt - 1.f;
    } else if (dt > 1.f - osc->freq.frequency_norm) {
        dt = (dt - 1.f) / osc->freq.frequency_norm;
        polyBLEP = 2*dt + dt*dt  + 1.f; 
    }
    sample -= polyBLEP;
    osc->phase += osc->freq.incr_phase;
    osc->phase = (osc->phase >= AudIO::twoPI) ? (osc->phase - AudIO::twoPI) : osc->phase;
    *osc->path.out = sample * osc->gain;// * out_adsr(osc->adsr);
    
    if (osc->path.in) *osc->path.out *= *osc->path.in;

}

Oscillator* init_osc(AAllocator& alloc,float freq = 440.f, float gain = .7f, WaveType type = SINE);
