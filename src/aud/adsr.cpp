#include "adsr.h"
#include "allocator.h"

void init_adsr(ADSR* adsr) {

   adsr->state.store(ADSR::Fade);

   adsr->env[ADSR::Attack].start = 0;
   adsr->env[ADSR::Attack].end = 1.0;

   adsr->env[ADSR::Attack].length = 2000;

   adsr->env[ADSR::Decay].start = 1.0;
   adsr->env[ADSR::Decay].end = 0.4;
   adsr->env[ADSR::Decay].bend = 0.8;
   adsr->env[ADSR::Decay].length = 5000;
   adsr->env[ADSR::Decay].shape = ADSR::CurveShape::quad;

   adsr->env[ADSR::Sustain].start = 0.4;
   adsr->env[ADSR::Sustain].end = 0.4;
   adsr->env[ADSR::Sustain].length = 5000;

   adsr->env[ADSR::Release].start = 0.4;
   adsr->env[ADSR::Release].end = 0.0;
   adsr->env[ADSR::Release].bend = 0.4;

   adsr->env[ADSR::Release].length = 2400;
   adsr->env[ADSR::Release].shape = ADSR::CurveShape::quad;
   adsr->env[ADSR::Fade].length = 3000;
   adsr->env[ADSR::Fade].bend = 0.6;
   adsr->env[ADSR::Release].bend = 0.4;

   adsr->env[ADSR::Fade].shape = ADSR::CurveShape::quad;

}

float out_adsr (ADSR* adsr) {

   switch(adsr->state.load()) {
      case ADSR::Off:
         return AudIO::SampleSilence;
         break;
      case ADSR::Fade:
         // Delay Env Retrigger
         adsr->pos = (float)adsr->fade_index / adsr->env[ADSR::Fade].length;
         adsr->fade_index++;
         if (adsr->fade_index >= adsr->env[ADSR::Fade].length - 1) {
            adsr->index = 0;
            adsr->fade_index = 0;
            adsr->state.store(adsr->next_state);
         }
         adsr->last_sample = adsr->env[ADSR::Fade].out(adsr->pos);
         return adsr->last_sample;
         break;

      case ADSR::Attack:
         adsr->pos = (float)adsr->index / adsr->env[ADSR::Attack].length;
         adsr->index++;
         if (adsr->index >= adsr->env[ADSR::Attack].length - 1) {
            adsr->index = 0;
            adsr->state.store(ADSR::Decay);
         }
         adsr->last_sample = adsr->env[ADSR::Attack].out(adsr->pos);
         return adsr->last_sample;
         break;
      case ADSR::Decay:
         adsr->pos = (float)adsr->index / adsr->env[ADSR::Decay].length;
         adsr->index++;
         if (adsr->index >= adsr->env[ADSR::Decay].length - 1) {
            adsr->index = 0;
            adsr->state.store(ADSR::Sustain);
         }
         adsr->last_sample = adsr->env[ADSR::Decay].out(adsr->pos);
         return adsr->last_sample;
         break;
      case ADSR::Sustain:
         adsr->pos = (float)adsr->index / adsr->env[ADSR::Sustain].length;
         adsr->index++;
         if (adsr->index >= adsr->env[ADSR::Sustain].length - 1) {
            adsr->index--;
            //Sustain changes only after NoteOff event to Release
         }
         adsr->last_sample = adsr->env[ADSR::Sustain].out(adsr->pos);
         return adsr->last_sample;
         break;
      case ADSR::Release:
         adsr->pos = (float)adsr->index / adsr->env[ADSR::Release].length;
         adsr->index++;
         if (adsr->index >= adsr->env[ADSR::Release].length - 1) {
            adsr->index = 0;
            adsr->state.store(ADSR::Off);
         }
         adsr->last_sample = adsr->env[ADSR::Release].out(adsr->pos);
         return adsr->last_sample;
         break;
      default:
         break;

   } 
   return AudIO::SampleSilence;

}

void fade_into_adsr (ADSR* adsr, ADSR::State next) {
    adsr->next_state = next;  
    adsr->env[ADSR::Fade].start = adsr->last_sample; 
    adsr->env[ADSR::Fade].end = adsr->env[adsr->next_state].start;
    adsr->fade_index = 0;
    adsr->state.store(ADSR::Fade);
}


