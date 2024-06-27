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
   
   auto tock = resources.addWAV("res/tock.wav").get();
   auto kick = resources.addWAV("res/kick.wav").get();
   af.set_OutDevice(devID);
   af.master()->add_channel();
   af.master()->add_channel();

   af.master()->channel(0)
      ->set_gain(0.7)
      .add_event({tock, timeFromBeats(3, 0)});
   af.master()->channel(1)
      ->set_gain(0.7)
      .add_event({kick, timeFromBeats(5, 0)});
    af.play();
    std::cin.get();
    return 0;
}
