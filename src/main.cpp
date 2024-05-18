#include <iostream>
#include "audiointerface.h"
#include "oscillator.h"
int main (int argc, char *argv[]) {
    AudioInterface af {};
    af.set_OutDevice(1)
        .master()
            ->add_channel()->add_source(std::make_unique<SineOscillator>(440.f));
    af.play();
    std::cin.get();
    return 0;
}
