#include "oscillator.h"


// void send_midi(int type, int note) {
//     if (type == 1) {
//         set_freq(440.0 * pow(2,((note - 69.0f))/12.0f));
//         adsr.state.store(ADSR::State::Attack);
//     } else if (type == 2) {
//         ADSR::State state = adsr.state.load();
//         if (state == ADSR::State::Off || state == ADSR::State::Release) return;
//         adsr.fade_into(ADSR::State::Release); 
//     }
// }


Oscillator* init_osc(AAllocator& alloc, float freq, float gain, WaveType type) {
    Oscillator* osc = (Oscillator*) allocate_aa(alloc, sizeof(Oscillator));
    //init_adsr(osc->adsr);
    set_freq(osc->freq, freq); 
    set_gain(osc->gain, gain);
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
    return osc;
}


