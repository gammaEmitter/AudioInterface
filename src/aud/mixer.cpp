#include "mixer.h"
#include "iodef.h"

/*
 * TODO:debug here
 */
void init_mixer(AAllocator& alloc, Mixer*& mixer) {
   mixer = (Mixer*) allocate_aa(alloc, sizeof(Mixer));
   for (int i = 0; i < 4096; ++i) {
      mixer->paths[i] = nullptr;
      mixer->out_signals[i] = 0.f;
   }
   for (int i = 0; i < 128; ++i) {
      mixer->ch_signals[i] = nullptr;
      mixer->used_signals[i] = 0;
      mixer->order_channel[i] = 0;
   }
   mixer->channels_in_use = 0;

   
}

uint16_t mixer_signal_add(Mixer* mixer, SignalPath* path, uint8_t channel) {

   uint16_t index = ((channel - 1) * 32) + mixer->used_signals[channel - 1];

   path->out = &mixer->out_signals[index];
   if(mixer->used_signals[channel - 1] > 0) {
      path->in = &mixer->out_signals[index - 1];
   };

   mixer->paths[index] = path;
   mixer->paths[index]->out = path->out;
   mixer->paths[index]->in = path->in;
   mixer->paths[index]->proc = path->proc;
   mixer->ch_signals[channel - 1] = &mixer->out_signals[index];
   
   mixer->used_signals[channel - 1]++;
   mixer->order_channel[mixer->channels_in_use] = channel - 1;
   mixer->channels_in_use++;
   return index;
}

float sum_mixer(Mixer* mixer) {

   float total_sum = AudIO::SampleSilence;
   uint16_t index;
   for (int num_ch = 0; num_ch  < mixer->channels_in_use; ++num_ch) {
      index =  (mixer->order_channel[num_ch]) * 32;
      for (int num_sig = 0; num_sig < mixer->used_signals[mixer->order_channel[num_ch]]; ++num_sig, ++index) {
         //casting signalpath pointer to the osc/eventmap/... pointer
         // this assumes that SignalPath is the first struct of a generator
         // like osc or eventmap 
         mixer->paths[index]->proc((void*)mixer->paths[index]);
      }
      total_sum += *mixer->ch_signals[mixer->order_channel[num_ch]];
   }
   // set_clampabs1(total_sum, total_sum);
   return total_sum;
}
