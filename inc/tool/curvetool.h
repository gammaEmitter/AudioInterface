#pragma once
#include "iodef.h"
#include <vector>
#include <cmath>
#include <variant>

using CurveFunction = std::variant<std::function
<float(float,float,float,float)>, std::function<float(float,float,float)>>;

enum CurveShape {
    unity,
    linear,
    quad,
};

inline float linearCurve (float start, float end, float pos) {
    return (end - start) * pos + start;
}
//bend 0..1 or 1..10+
// end = value at pos = 1.0
// pos == (index/length)


inline float quadCurve(float start, float end, float bend,  float pos) {
    return (end - start) * pow(pos, bend) + start;
}


struct CurveModel {
    CurveShape      shape   = linear;
    uint32_t        length  {};
    uint32_t        offset  {};
    float           start   {};
    float           end     {};
    float           bend    = 1.f;

    float out(float pos) {
        switch(shape) {
            case linear:
                return linearCurve(start,end, pos);
            case quad:
                return quadCurve(start, end, bend, pos);
            case unity:
                return 1;
        }
        ;
    }
};

void short_fade_in(CurveModel& model, uint32_t len);
void short_fade_out(CurveModel& model, uint32_t len);
