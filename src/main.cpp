#include <iostream>
#include <memory>
#include "audiointerface.h"
#include "oscillator.h"
#include "metronome.h"

int main (int argc, char *argv[]) {
    AudioInterface af {};
    af.set_OutDevice(1)
        .master()
            ->add_channel()->add_source(std::make_unique<Metronome>());
            //->add_channel();
    //af.master()->add_channel()->add_source(std::make_unique<SineOscillator>(440.f));
    af.play();
    std::cin.get();
    return 0;
}
