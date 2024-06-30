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
   auto osc1 = SineOscillator(440.f);
   auto adsr = ADSR();
   auto midi_ch1 = af.master()->add_channel_midi();
   auto oscOut = std::bind(&SineOscillator::Out, &osc1);
   auto adsrOut = std::bind(&ADSR::Out, &adsr);    
   adsr.set_source(oscOut);
   midi_ch1->add_source(adsrOut);
   midi_ch1->set_midi(&osc1, &adsr);
   printf("Osc(main): %p\n", &(osc1));
   printf("ADSR(main): %p\n", &(adsr));
   adsr.env[ADSR::Attack].start = 0;
   adsr.env[ADSR::Attack].end = 1.0;

   adsr.env[ADSR::Attack].length = 1000;

   adsr.env[ADSR::Decay].start = 1.0;
   adsr.env[ADSR::Decay].end = 0.4;
   adsr.env[ADSR::Decay].bend = 0.8;
   adsr.env[ADSR::Decay].length = 5000;
   adsr.env[ADSR::Decay].shape = ADSR::CurveShape::quad;

   adsr.env[ADSR::Sustain].start = 0.4;
   adsr.env[ADSR::Sustain].end = 0.4;
   adsr.env[ADSR::Sustain].length = 5000;

   adsr.env[ADSR::Release].start = 0.4;
   adsr.env[ADSR::Release].end = 0.0;
   adsr.env[ADSR::Release].bend = 0.4;

   adsr.env[ADSR::Release].length = 30000;
   adsr.env[ADSR::Release].shape = ADSR::CurveShape::quad;
   adsr.env[ADSR::Fade].length = 4000;
   adsr.env[ADSR::Fade].bend = 0.6;
;
   adsr.env[ADSR::Release].bend = 0.4;

   adsr.env[ADSR::Fade].shape = ADSR::CurveShape::quad;
   auto tock = resources.addWAV("res/tock.wav").get();
   auto kick = resources.addWAV("res/kick.wav").get();
   af.set_OutDevice(devID);

   af.play();
   std::cin.get();
   return 0;
}
