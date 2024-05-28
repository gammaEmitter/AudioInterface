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
    auto kick = resources.addWAV("kick.wav");
    auto tock = resources.addWAV("tock.wav");
    AudioEvent ev1 = AudioEvent(kick.get(), timeFromBeats(1, 0));
    AudioEvent ev2 = AudioEvent(kick.get(), timeFromBeats(2, 0));
    AudioEvent ev3 = AudioEvent(kick.get(), timeFromBeats(3, 0));
    AudioEvent ev4 = AudioEvent(kick.get(), timeFromBeats(4, 0));
    AudioEvent ev5 = AudioEvent(kick.get(), timeFromBeats(5, 0));
    AudioEvent ev6 = AudioEvent(kick.get(), timeFromBeats(6, 0));
    AudioEvent ev7 = AudioEvent(kick.get(), timeFromBeats(7, 0));
    AudioEvent ev8 = AudioEvent(kick.get(), timeFromBeats(8, 0));
    
    af.set_OutDevice(devID);
    //af.master()->add_channel()->add_source(std::make_unique<Metronome>());
    af.master()->add_channel()->add_event(ev1)
                                .add_event(ev2)
                                .add_event(ev3)
                                .add_event(ev4)
                                .add_event(ev5)
                                .add_event(ev6)
                                .add_event(ev7)
                                .add_event(ev8);
    //af.master()->add_channel()->add_source(std::make_unique<SineOscillator>(440.f));
    af.play();
    std::cin.get();
    return 0;
}
