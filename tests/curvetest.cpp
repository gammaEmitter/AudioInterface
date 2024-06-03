#include "curvetool.h"
#include "adsr.h"

#include <fstream>
#include <iostream>

int main (int argc, char *argv[]) {
    
    ADSR adsr {};
    adsr.source = [](){return 1.f;};

    adsr.last_sample = 0.f;

    adsr.env[ADSR::Attack].start = 0;
    adsr.env[ADSR::Attack].end = 1.0;
    adsr.env[ADSR::Attack].length = 10;

    adsr.env[ADSR::Decay].start = 1.0;
    adsr.env[ADSR::Decay].end = 0.4;
    adsr.env[ADSR::Decay].bend = 0.8;
    adsr.env[ADSR::Decay].length = 50;
    adsr.env[ADSR::Decay].shape = ADSR::CurveShape::quad;

    adsr.env[ADSR::Sustain].start = 0.4;
    adsr.env[ADSR::Sustain].end = 0.4;
    adsr.env[ADSR::Sustain].length = 50;

    adsr.env[ADSR::Release].start = 0.4;
    adsr.env[ADSR::Release].end = 0.0;
    adsr.env[ADSR::Release].bend = 0.4;

    adsr.env[ADSR::Release].length = 300;
    adsr.env[ADSR::Release].shape = ADSR::CurveShape::quad;


    std::vector<float> res {};

    adsr.state = ADSR::Off;
    adsr.fade_into(ADSR::Attack);
    adsr.index = 0;
    for (int i = 0; i < 94; ++i) {
        res.push_back(adsr.Out());
    }
    adsr.fade_into(ADSR::Attack);
    adsr.index = 0;
    for (int i = 0; i < adsr.env[ADSR::Release].length; ++i) {
        res.push_back(adsr.Out());
    }
    std::ofstream outfile {};
    outfile.open("adsr_curve_test.dat");
    for (auto val : res) {
        char array[10];
        snprintf(array, sizeof(array), "%f", val);
        outfile.write(array, 10);
        outfile.write("\n", 2);

    }
    outfile.close();



    return 0;
}
