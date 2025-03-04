#include "iodef.h"
#include "filter/biquad.h"

void init_filter_biquad(BiquadFilter* filter, FilterType type, float freq) {
   filter->q_factor = 1;
   filter->in_prev[0] = 0;
   filter->in_prev[1] = 0;
   filter->out_prev[0] = 0;
   filter->out_prev[1] = 0;
   filter->path.proc = &out_filter_biquad;
   calc_coe_filter_biquad(filter, type, freq);

}

void calc_coe_filter_biquad(BiquadFilter* filter, FilterType type, float freq) {
   float center_freq = AudIO::twoPI*(freq/(float)AudIO::Samplerate44100);

   float sin_w = sin(center_freq);
   float cos_w = cos(center_freq);
   float alpha = sin_w / (2*filter->q_factor);

   switch (type) {
      case FilterType::lowpass:
         filter->coe_a[0] = 1 + alpha;
         filter->coe_a[1] = -2*cos_w;
         filter->coe_a[2] = 1 - alpha;

         filter->coe_b[0] = (1-cos_w)/2;
         filter->coe_b[1] = (1-cos_w);
         filter->coe_b[2] = (1-cos_w)/2;
         break;
      case FilterType::highpass:
         filter->coe_a[0] = 1 + alpha;
         filter->coe_a[1] = -2*cos_w;
         filter->coe_a[2] = 1 - alpha;

         filter->coe_b[0] = (1+cos_w)/2;
         filter->coe_b[1] = -(1+cos_w);
         filter->coe_b[2] = (1+cos_w)/2;
         break;

      default:

         break;
   }

   filter->constants_directform_I[0] = filter->coe_b[0] / filter->coe_a[0];
   filter->constants_directform_I[1] = filter->coe_b[1] / filter->coe_a[0];
   filter->constants_directform_I[2] = filter->coe_b[2] / filter->coe_a[0];
   filter->constants_directform_I[3] = filter->coe_a[1] / filter->coe_a[0];
   filter->constants_directform_I[4] = filter->coe_a[2] / filter->coe_a[0];

}
