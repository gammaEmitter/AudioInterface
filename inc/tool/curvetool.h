#pragma once
#include "iodef.h"
#include <vector>
#include <cmath>
#include <variant>

class Curve {};

inline float linearCurve (float start, float end, float pos) {
    return (end - start) * pos + start;
}
//bend 0..1 or 1..10+
// end = value at pos = 1.0
// pos == (index/length)


inline float quadCurve(float start, float end, float bend,  float pos) {
    return (end - start) * pow(pos, bend) + start;
}

using CurveFunction = std::variant<std::function
<float(float,float,float,float)>, std::function<float(float,float,float)>>;
