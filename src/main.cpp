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
    AudioInterface af {};
    if (argc < 2) {
        std::cout << "\nUsage: " << argv[0] << " <ID>" << "\n"; 
        return -1;
    }
    std::string id {argv[1]};
    int devID = std::stoi(id);
    
    auto kick = resources.addWAV("res/kick.wav").get();
    auto tock = resources.addWAV("res/tock.wav").get();
    
    af.set_OutDevice(devID);
    af.master()->add_channel()
       ->add_event({kick, timeFromBeats(0, 0)})
        .add_event({kick, timeFromBeats(1, 0)})
        .add_event({kick, timeFromBeats(2, 0)})
        .add_event({kick, timeFromBeats(3, 0)})
        .add_event({kick, timeFromBeats(4, 0)})
        .add_event({kick, timeFromBeats(5, 0)});
    //af.master()->add_channel()->add_source(std::make_unique<SineOscillator>(440.f));
    af.play();
    std::cin.get();
    return 0;
}
