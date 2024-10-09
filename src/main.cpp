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
   auto mod = resources.addWAV("res/mod.wav").get();
   af.set_OutDevice(devID);

   SineOscillator osc {440.f};
   ChannelMidi* ch_midi = af.master()->add_channel_midi();
   ch_midi->set_instrument(&osc);
   ch_midi->add_event({timeFromBeats(0,0), timeFromBeats(1,0), 60});
   ch_midi->add_event({timeFromBeats(2,0), timeFromBeats(1,0), 65});
   ch_midi->add_event({timeFromBeats(4,0), timeFromBeats(1,0), 70});
   ch_midi->add_event({timeFromBeats(6,0), timeFromBeats(1,0), 75});

   // ChannelAudio* ch_aud1 = af.master()->add_channel_audio();
   // Clockbase::loop_active = true;
   // Clockbase::loop_in = timeFromBeats(0,0);
   // Clockbase::loop_out = timeFromBeats(8,0);
   // auto ev = AudioEvent(mod, 0);
   // auto t = beatsFromTime(ev.duration);
   // ch_aud1->set_gain(0.7);
   // ch_aud1->add_event({kick, timeFromBeats(0, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(1, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(2, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(3, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(4, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(9, 36)});
   // ch_aud1->add_event({kick, timeFromBeats(10, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(12, 0)});
   // ch_aud1->add_event({kick, timeFromBeats(13, 0)});
   // ch_aud1->add_event({mod, timeFromBeats(1, 0)});
   // ch_aud1->add_event({mod, timeFromBeats(3, 0)});
   // ch_aud1->add_event({tock, timeFromBeats(11, 0)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 0)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 8)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 16)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 24)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 32)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 40)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 48)});
   // ch_aud1->add_event({tock, timeFromBeats(15, 56)});
   //

   af.play();
   std::cin.get();
   af.stop();
   return 0;
}
