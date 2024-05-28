#include <iostream>
#include <memory>
#include "audioevent.h"
#include "audiointerface.h"
#include "clockbase.h"
#include "oscillator.h"
#include "metronome.h"
#include "resourcemanager.h"


ResourceManager &resources{ResourceManager::getInstance()};

int main (int argc, char *argv[]) {

    std::string id {argv[1]};
    int devID = std::stoi(id);
    
    AudioInterface af {};

    resources.addWAV("kick.wav");
    AudioEvent ev1 = AudioEvent(resources.getFile("kick.wav").get(), 120000);
    

    af.set_OutDevice(devID)
        .master()
            ->add_channel()->add_source(std::make_unique<Metronome>());
    af.master()->add_channel()->add_event(ev1);
    //af.master()->add_channel()->add_source(std::make_unique<SineOscillator>(440.f));
    af.play();
    std::cin.get();
    return 0;
}
