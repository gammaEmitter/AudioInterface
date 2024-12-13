#include <iostream>

#include <memory>
#include <functional>
#include <strings.h>
#include "../allocator.h"
#include "audioevent.h"
#include "audioeventmap.h"
#include "audiointerface.h"
#include "clockbase.h"
#include "adsr.h"
#include "iodef.h"
#include "midievent.h"
#include "oscillator.h"
#include "wavetable.h"
#include "wtoscillator.h"
#include "metronome.h"
#include "resourcemanager.h"

#define OSC1_CH 3
#define EVENTMAP1_CH 4
#define EVENTMAP2_CH 1

ResourceManager &resources{ResourceManager::getInstance()};

int main (int argc, char *argv[]) {
   AAllocator mem_devices {};
   init_allocator(mem_devices, 65536);
   AudioInterface af;
   init_audio_interface(af);
   af.mixer = init_mixer(mem_devices);


   if (argc < 2) {
      std::cout << "\nUsage: " << argv[0] << " <ID>" << "\n"; 
      return -1;
   }
   std::string id {argv[1]};
   int devID = std::stoi(id);
   auto kick = resources.addWAV("res/kick.wav").get();
   auto bass = resources.addWAV("res/bass.wav").get();
   set_odevice(af, devID);

   Oscillator* osc = init_osc(mem_devices, 110, 0.7, SINE);
   // BAD ACCESS osc->adsr.state.store(ADSR::Attack);
   //

   AudioEventMap* aem = init_audio_event_map(mem_devices);
   AudioEventMap* bass_events = init_audio_event_map(mem_devices);



   Clockbase::loop_active = true;
   Clockbase::loop_in = 0;
   Clockbase::loop_out =  timeFromBeats(1,0);

   printf("osc index: %u\n",mixer_signal_add(af.mixer, &osc->path, OSC1_CH));
   set_gain(osc->gain, 0.3);
   printf("aem index: %u\n",mixer_signal_add(af.mixer, &aem->path, EVENTMAP1_CH));
   printf("bass_events index: %u\n",mixer_signal_add(af.mixer, &bass_events->path, EVENTMAP2_CH));
   add_event_audio_event_map(aem, audio_event(mem_devices,kick, timeFromBeats(0,0)));
   add_event_audio_event_map(bass_events, audio_event(mem_devices,bass, timeFromBeats(0,16)));
   add_event_audio_event_map(bass_events, audio_event(mem_devices,bass, timeFromBeats(0,32)));
   add_event_audio_event_map(bass_events, audio_event(mem_devices,bass, timeFromBeats(0,48)));

   play_interface(af);
   std::cin.get();
   free(mem_devices.mem);
   stop_interface(af);
   return 0;
}
