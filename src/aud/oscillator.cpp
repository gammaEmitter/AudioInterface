#include "oscillator.h"

void init_osc(Oscillator* osc, float freq, float gain, WaveType type) {

    init_adsr(osc->adsr);
    set_freq(&osc->freq, freq); 
    set_clampabs1(osc->gain, gain);
    switch (type) {
        case SINE:
            osc->path.proc = &out_osc_sine;
            break;
        case SAW:
            osc->path.proc = &out_osc_saw;
            break;
        case TRIANGLE:
            // osc.out_fn = [&]() { return out_osc_saw(osc);};
            break;
        case SQUARE:
            // osc.out_fn = [&]() { return out_osc_saw(osc);};
            break;
    }
}


