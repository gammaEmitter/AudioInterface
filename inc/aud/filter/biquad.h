#pragma once

#include "allocator.h"
#include "iodef.h"
#include "libremidi/libremidi-c.h"
#include <vector>
#include <functional>

/* 
 *  --- DIRECT FORM I --- DIFFERENCE EQUATION ---
 *
 * y[n] = (b0/a0) * x[n]
 *      
 *      + (b1/a0) * x[n-1]
 *      + (b2/a0) * x[n-2]
 *
 *      - (a1/a0) * y[n-1]
 *      - (a2/a0) * y[n-2]
 *
 *
 * */
enum FilterType {
    lowpass,
    highpass
};
struct BiquadFilter {
    SignalPath path;
    float in_prev[2] {0};
    float out_prev[2] {0};
    float coe_a[3] {0};
    float coe_b[3] {0};
    float constants_directform_I[5] {0};
    float shelf;
    float q_factor;
    float gain;
    u8 bandwidth;

    
};

void init_filter_biquad(BiquadFilter* filter, FilterType type, float freq);
void calc_coe_filter_biquad(BiquadFilter* filter, FilterType type, float freq);

inline void out_filter_biquad(void* arg) {
    BiquadFilter* filter = (BiquadFilter*) arg;
    float sample = filter->constants_directform_I[0] * (*filter->path.in)
                   + filter->constants_directform_I[1] * filter->in_prev[0]
                   + filter->constants_directform_I[2] * filter->in_prev[1]
                   - filter->constants_directform_I[3] * filter->out_prev[0]
                   - filter->constants_directform_I[4] * filter->out_prev[1];
    *filter->path.out = sample * filter->gain;

    filter->in_prev[1] = filter->in_prev[0];
    filter->out_prev[1] = filter->out_prev[0];
    filter->in_prev[0] = *filter->path.in;
    filter->out_prev[0] = sample;
    return;
}
