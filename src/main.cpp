#include <iostream>
#include "audiointerface.h"
int main (int argc, char *argv[]) {
    


    AudioInterface af {};
    af.set_OutDevice(2)
        .master()
            ->add_channel()
                ->add_source(std::make_unique<SawOscillator>(440.f));
    af.set_InDevice(2);
    af.play();
    std::cin.get();
    return 0;
}
