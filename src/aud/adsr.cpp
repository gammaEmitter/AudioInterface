#include "adsr.h"

/*
 *  ADSR module has ISignalSource as input
 *  receives MidiEvents and acts as a gate
 *
 */

//Note on A->D->S
//Note off ->R

void ADSR::set_source(SampleOut func){
    source = func;
}


void ADSR::fade_into (ADSR::State next) {
    next_state = next;
    env[ADSR::Fade].start = last_sample;
    env[ADSR::Fade].end = env[next_state].start;
    env[ADSR::Fade].length = 80;
    env[ADSR::Fade].bend = 0.7;
    env[ADSR::Fade].shape = ADSR::CurveShape::quad;
    index = 0;
    state.store(ADSR::Fade);
}
