#pragma once
#include "iodef.h"
#include "curvetool.h"
#include <chrono>
#include <atomic>
#include <unordered_map>



struct ADSR : public ISignalSource {
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
    
    ADSR();

    inline float Out() override {
        switch(state.load()) {
            case Off:
                return AudIO::SampleSilence;
                break;
            case Fade:
                // Delay Env Retrigger
                pos = (float)fade_index / env[Fade].length;
                fade_index++;
                if (fade_index >= env[Fade].length - 1) {
                    index = 0;
                    fade_index = 0;
                    state.store(next_state);
                }
                last_sample = env[Fade].out(pos);
                return last_sample;
                break;

            case Attack:
                pos = (float)index / env[Attack].length;
                index++;
                if (index >= env[Attack].length - 1) {
                    index = 0;
                    state = Decay;
                }
                last_sample = env[Attack].out(pos);
                return last_sample;
                break;
            case Decay:
                pos = (float)index / env[Decay].length;
                index++;
                if (index >= env[Decay].length - 1) {
                    index = 0;
                    state = Sustain;
                }
                last_sample = env[Decay].out(pos);
                return last_sample;
                break;
            case Sustain:
                pos = (float)index / env[Sustain].length;
                index++;
                if (index >= env[Sustain].length - 1) {
                    index--;
                    //Sustain changes only after NoteOff event to Release
                }
                last_sample = env[Sustain].out(pos);
                return last_sample;
                break;
            case Release:
                pos = (float)index / env[Release].length;
                index++;
                if (index >= env[Release].length - 1) {
                    index = 0;
                    state = Off;
                }
                last_sample = env[Release].out(pos);
                return last_sample;
                break;
            default:
                break;

        } 
        return AudIO::SampleSilence;
    }
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
