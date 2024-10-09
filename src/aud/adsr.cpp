#include "adsr.h"

/*
 *  ADSR module has ISignalSource as input
 *  receives MidiEvents and acts as a gate
 *
 */

//Note on A->D->S
//Note off ->R

ADSR::ADSR() {

   env[ADSR::Attack].start = 0;
   env[ADSR::Attack].end = 1.0;

   env[ADSR::Attack].length = 250;

   env[ADSR::Decay].start = 1.0;
   env[ADSR::Decay].end = 0.4;
   env[ADSR::Decay].bend = 0.8;
   env[ADSR::Decay].length = 5000;
   env[ADSR::Decay].shape = ADSR::CurveShape::quad;

   env[ADSR::Sustain].start = 0.4;
   env[ADSR::Sustain].end = 0.4;
   env[ADSR::Sustain].length = 5000;

   env[ADSR::Release].start = 0.4;
   env[ADSR::Release].end = 0.0;
   env[ADSR::Release].bend = 0.4;

   env[ADSR::Release].length = 15000;
   env[ADSR::Release].shape = ADSR::CurveShape::quad;
   env[ADSR::Fade].length = 2000;
   env[ADSR::Fade].bend = 0.6;
   env[ADSR::Release].bend = 0.4;

   env[ADSR::Fade].shape = ADSR::CurveShape::quad;

}

void ADSR::fade_into (ADSR::State next) {
    next_state = next;  
    env[ADSR::Fade].start = last_sample; 
    env[ADSR::Fade].end = env[next_state].start;
    fade_index = 0;
    state.store(ADSR::Fade);
}

