#pragma once
#include "iodef.h"
#include "curvetool.h"
#include <chrono>
#include <atomic>
#include <unordered_map>



struct ADSR {
    enum State {
        Off,
        Fade,
        Attack,
        Decay,
        Sustain,
        Release,
        };
    enum CurveShape {
        linear,
        quad,
    };

    struct Model {
        CurveShape      shape   = linear;
        u32             length  {};
        float           start   {};
        float           end     {};
        float           bend    = 1.f;

        float out(float pos) {
            switch(shape) {
                case linear:
                    return linearCurve(start,end, pos);
                case quad:
                    return quadCurve(start, end, bend, pos);
                default:
                    return AudIO::SampleSilence;
            }
        }
    };
    void fade_into (ADSR::State next);
    

    using ADSR_data_t = std::unordered_map<ADSR::State, Model>;

    u32                 index           {};
    u32                 fade_index      {};
    std::atomic<State>  state           = State::Off;
    ADSR_data_t         env             {};
    float               pos             {};
    float               last_sample     {};
    State               next_state      = State::Attack;
};

using ADSR_opt = std::optional<ADSR>;

float out_adsr (ADSR& adsr);
void init_adsr(ADSR& adsr);
