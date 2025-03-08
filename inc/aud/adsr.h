#pragma once
#include "iodef.h"
#include "curvetool.h"
#include "allocator.h"
#include <chrono>
#include <atomic>
#include <unordered_map>



struct ADSR {
    enum State {
        Attack,
        Decay,
        Sustain,
        Release,
        Fade,
        Off,
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

    };
    


    u32                 index           {};
    u32                 fade_index      {};
    std::atomic<State>  state           = State::Off;
    Model               env[5]          {};
    float               pos             {};
    float               last_sample     {};
    State               next_state      = State::Attack;
};

float out_model(ADSR::Model* model, float pos);
void init_adsr(ADSR* adsr);
float out_adsr (ADSR* adsr);
void fade_into_adsr(ADSR* adsr, ADSR::State next);
