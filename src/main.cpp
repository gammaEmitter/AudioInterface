#include <iostream>
#include <memory>
#include "audioevent.h"
#include "audiointerface.h"
#include "clockbase.h"
#include "iodef.h"
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

   ChannelAudio* ch_aud1 = af.master()->add_channel_audio();
   Clockbase::loop_active = true;
   Clockbase::loop_in = timeFromBeats(0,0);
   Clockbase::loop_out = timeFromBeats(4,10);
   ch_aud1->set_gain(0.7);
   ch_aud1->add_event({kick, timeFromBeats(0, 0)});
   ch_aud1->add_event({kick, timeFromBeats(1, 0)});
   ch_aud1->add_event({kick, timeFromBeats(2, 0)});
   ch_aud1->add_event({kick, timeFromBeats(3, 0)});
   ch_aud1->add_event({kick, timeFromBeats(4, 0)});
   ch_aud1->add_event({kick, timeFromBeats(5, 0)});
   ch_aud1->add_event({kick, timeFromBeats(6, 0)});
   ch_aud1->add_event({kick, timeFromBeats(7, 0)});

   af.play();
   std::cin.get();
   return 0;
}
