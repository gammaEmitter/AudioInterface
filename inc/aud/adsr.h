#pragma once
#include "iodef.h"
#include "curvetool.h"
#include <unordered_map>



struct ADSR : public ISignalSource {
    enum State {
        Off,
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
        uint32_t        length  {};
        float           start   {};
        float           end     {};
        float           bend    {};

        float out(float pos) {
            switch(shape) {
                case linear:
                    return linearCurve(start,end, pos);
                case quad:
                    return quadCurve(start, end, bend, pos);
            }
            ;
        }
    };

    

    inline float Out() override {
        float pos {};
        index++;
        switch(state) {;
            case Off:
                return AudIO::SampleSilence;
                break;
            case Attack:
                pos = (float)index / env[Attack].length;
                if (index == env[Attack].length - 1) {
                    index = 0;
                    state = Decay;
                }
                return source() * env[Attack].out(pos);
                break;
            case Decay:
                pos = (float)index / env[Decay].length;
                if (index == env[Decay].length - 1) {
                    index = 0;
                    state = Sustain;
                }
                return source() * env[Decay].out(pos);
                break;
            case Sustain:
                pos = (float)index / env[Sustain].length;
                if (index == env[Sustain].length - 1) {
                    index--;
                    //Sustain changes only after NoteOff event to Release
                }
                return source() * env[Sustain].out(pos);
                break;
            case Release:
                pos = (float)index / env[Release].length;
                if (index == env[Release].length - 1) {
                    index = 0;
                    state = Off;
                }
                return source() * env[Release].out(pos);
                break;
            default:
                break;

        } 
        return AudIO::SampleSilence;
    }
    using ADSR_data_t = std::unordered_map<ADSR::State, Model>;

    SampleOut           source          {};
    uint32_t            index           {};
    State               state           = State::Off;
    ADSR_data_t         env             {};
};


