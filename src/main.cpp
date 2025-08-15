#include <climits>
#include <iostream>

#include <memory>
#include <functional>
#include <strings.h>
#include <thread>
#include "../allocator.h"
#include "audioevent.h"
#include "audioeventmap.h"
#include "audiointerface.h"
#include "bouce.h"
#include "clockbase.h"
#include "adsr.h"
#include "curvetool.h"
#include "filter/biquad.h"
#include "iodef.h"
#include "midievent.h"
#include "midieventmap.h"
#include "mixer.h"
#include "oscillator.h"
#include "wavetable.h"
#include "wavtool.h"
#include "wtoscillator.h"
#include "metronome.h"
#include "resourcemanager.h"
#include "filter/biquad.h"
#include "filter/delay.h"
#include "bouce.h"
#include <thread>

#define SZ_ALLOC 10 * 1024 * 1024

#define OSC1_CH 3
#define CH_1_EVENTMAP 4
#define CH2_EVENTMAP 1
#define CH3_EVENTMAP 115
#define EVENTMAP4_CH 17
#define EVENTMAP5_CH 16
#define EVENTMAP6_CH 18

ResourceManager &resources{ResourceManager::getInstance()};

int main (int argc, char *argv[]) {
   AAllocator mem_devices {};
   init_allocator(mem_devices, SZ_ALLOC);
   AudioInterface af;
   init_audio_interface(af);
   init_mixer(mem_devices, af.mixer);


   if (argc < 2) {
      std::cout << "\nUsage: " << argv[0] << " <ID>" << "\n"; 
      return -1;
   }
   std::string id {argv[1]};
   int devID = std::stoi(id);
   set_odevice(af, devID);

   auto kick = resources.addWAV(mem_devices, "res/kick.wav");
   auto bass = resources.addWAV(mem_devices, "res/bass.wav");
   auto tock = resources.addWAV(mem_devices, "res/tock.wav");
   auto hats = resources.addWAV(mem_devices, "res/hats.wav");
   auto tamb =  resources.addWAV(mem_devices, "res/tamb.wav");
   auto stick_wide =  resources.addWAV(mem_devices, "res/stick_wide.wav");
   //
   Oscillator* osc = (Oscillator*) allocate_aa(mem_devices, sizeof(Oscillator));
   osc->adsr = (ADSR*) allocate_aa(mem_devices, sizeof(ADSR)); 
   init_osc(osc, 4440, 0.7, SAW);
   osc->adsr->state.store(ADSR::Off);
   //
   // printf("im here\n");
   AudioEventMap* aem, *bass_events, *wide_events, *hats_events;
   init_audio_event_map(mem_devices, aem);
   init_audio_event_map(mem_devices, bass_events);
   init_audio_event_map(mem_devices, wide_events);
   init_audio_event_map(mem_devices, hats_events);
   MidiEventMap* osc_events;
   init_midi_event_map(mem_devices, osc_events, &osc->freq, osc->adsr);
   generator_set_midi_event_map(osc_events, &osc->path, false);
   BiquadFilter* biq2 = (BiquadFilter*) allocate_aa(mem_devices, sizeof(BiquadFilter));
   init_filter_biquad(biq2, FilterType::lowpass, 150.0);
   set_clampabs1(&biq2->gain, 0.7);
   BiquadFilter* biq = (BiquadFilter*) allocate_aa(mem_devices, sizeof(BiquadFilter));
   init_filter_biquad(biq, FilterType::highpass, 150.0);
   set_clampabs1(&biq->gain, 0.7);
   set_clampabs1(&osc->gain, 0.4);

   MixBus* bus1;
   init_mixbus(mem_devices, bus1);

   Delay* delay = (Delay*) allocate_aa(mem_devices,sizeof(Delay));
   init_delay(mem_devices, delay, timeFromBeats(1,32));
   delay->buf = (float*) allocate_aa(mem_devices, sizeof(float) * (delay->duration + 1));
   set_clampabs1(&delay->feedback, 0.5);
   Delay* delay2 = (Delay*) allocate_aa(mem_devices,sizeof(Delay));
   init_delay(mem_devices, delay2, timeFromBeats(0, 48));
   delay2->buf = (float*) allocate_aa(mem_devices, sizeof(float) * (delay2->duration + 1));
   set_clampabs1(&delay2->feedback, 0.4);





   Clockbase::loop_active = true;
   // Clockbase::loop_active = false;
   Clockbase::loop_in = 0;
   Clockbase::loop_out =  timeFromBeats(2,0);
   printf("aem index: %u\n",mixer_signal_add(af.mixer, &aem->path, CH_1_EVENTMAP));
   printf("bass index: %u\n",mixer_signal_add(af.mixer, &bass_events->path, CH2_EVENTMAP));
   printf("biq filter index: %u\n",mixer_signal_add(af.mixer, &biq2->path, CH2_EVENTMAP));
   u16 index_wide_events = mixer_signal_add(af.mixer, &wide_events->path, EVENTMAP4_CH);
   printf("hats index: %u\n",mixer_signal_add(af.mixer, &hats_events->path, EVENTMAP5_CH));
   // printf("biq filter index: %u\n",mixer_signal_add(af.mixer, &biq->path, CH2_EVENTMAP));
   // printf("delay2 on hats_events index: %u\n",mixer_signal_add(af.mixer, &delay2->path, EVENTMAP5_CH));
   u16 index_osc = mixer_signal_add(af.mixer, &osc->path, CH3_EVENTMAP);
   printf("osc_events index: %u\n",mixer_signal_add(af.mixer, &osc_events->path, CH3_EVENTMAP));
   printf("biq filter on osc_events index: %u\n",mixer_signal_add(af.mixer, &biq->path, CH3_EVENTMAP));
   // printf("delay on osc_events index: %u\n",mixer_signal_add(af.mixer, &delay->path, CH3_EVENTMAP));
   // u16 index_delay1 = mixer_signal_add(af.mixer, &delay->path, CH3_EVENTMAP);
   u8 index_osc1_on_mixbus = mixbus_signal_add(bus1, af.mixer->ch_signals[CH3_EVENTMAP - 1]);
   // u8 index_wide_events_on_mixbus = mixbus_signal_add(bus1, &af.mixer->out_signals[index_wide_events]);
   u8 index_wide_events_on_mixbus = mixbus_signal_add(bus1, &af.mixer->out_signals[index_wide_events]);
   u16 index_mixbus = mixer_signal_add(af.mixer, &bus1->path, EVENTMAP6_CH);
   printf("delay2 on mixbus index: %u\n",mixer_signal_add(af.mixer, &delay2->path, EVENTMAP6_CH));
   bus1->signals[index_osc1_on_mixbus].gain = 1.0f;
   bus1->signals[index_wide_events_on_mixbus].gain = 1.f;

   // BounceOffline* bounce1;
   // init_bounce_offline(mem_devices, bounce1,0, timeFromBeats(2, 0), true);
   //
   // u16 index_bounce = mixer_signal_add(af.mixer, &bounce1->path, EVENTMAP6_CH);

   auto ev1 = audio_event(mem_devices,kick, timeFromBeats(0,0));
   for (int i = 0; i < ev1->duration; ++i) { // TRUE
    if (abs(ev1->data[i]) > 1) printf("%s %f\n", __FUNCTION__ ,ev1->data[i]);
   }
   // short_fade_out(ev1->fade_out, 500);
   auto ev2 = audio_event(mem_devices,kick, timeFromBeats(1,0));
   auto b2 = audio_event(mem_devices,bass, timeFromBeats(0,32));
   auto h1 = audio_event(mem_devices, hats, timeFromBeats(1,0));
   auto b3 = audio_event(mem_devices,bass, timeFromBeats(0,48));
   auto b1 = audio_event(mem_devices,bass, timeFromBeats(0,16));
   auto b4 = audio_event(mem_devices,bass, timeFromBeats(1,16));
   auto b6 = audio_event(mem_devices,bass, timeFromBeats(1,48));
   auto b5 = audio_event(mem_devices,bass, timeFromBeats(1,32));

   add_event_audio_event_map(aem, ev1);
   add_event_audio_event_map(aem, ev2);
   add_event_audio_event_map(bass_events, b2);
   add_event_audio_event_map(bass_events, b6);
   add_event_audio_event_map(bass_events, b4);
   add_event_audio_event_map(bass_events, b1);
   add_event_audio_event_map(bass_events, b5);
   add_event_audio_event_map(bass_events, b3);
   remove_event_audio_event_map(bass_events, b4);
   remove_event_audio_event_map(bass_events, b5);
   remove_event_audio_event_map(bass_events, b6);
   // add_event_midi_event_map(osc_events, midi_event(mem_devices,timeFromBeats(1,0), NoteType::ON, 30));
   // add_event_midi_event_map(osc_events, midi_event(mem_devices,timeFromBeats(1,16), NoteType::OFF, 30));
   // add_event_audio_event_map(wide_events, audio_event(mem_devices,stick_wide, timeFromBeats(0,0)));
   for (int i = 0; i < osc_events->size_events; ++i) {
      printf("midi event (osc events) %d: %u\n",i, osc_events->events[i]->start_time);
   }
   for (int i = 0; i < bass_events->size_events; ++i) {
      printf("audio event (bass events) %d: start time %u ,data* %p,offset %d, duration %u at %p\n",i, bass_events->events[i]->start_time,bass_events->events[i]->data, bass_events->events[i]->offset,bass_events->events[i]->duration, bass_events->events[i]);
   }
   // auto hats_trunc = audio_event(mem_devices, hats, timeFromBeats(0,0));
   // add_event_audio_event_map(hats_events, hats_trunc);
   // add_event_audio_event_map(hats_events, audio_event(mem_devices, hats, timeFromBeats(1,0)));
   // add_event_audio_event_map(hats_events, audio_event(mem_devices, hats, timeFromBeats(1,32)));
   // for (int i = 0; i < sizeof(Mixer); ++i) {
   //    printf("%x", af.mixer[i]);
   //    if (i % 32 == 0) printf("\n");
   // }
   // printf("\n\n");
   // for (int i = 0; i < SZ_ALLOC; ++i) {
   //    printf("%x", mem_devices.mem[i]);
   //    if (i % 32 == 0) printf("\n");
   //   }
   //

  //  int c = 0;
  // auto t1 = std::thread([&c]() {
  //     bool expected_to_change = false;
  //     while(true) {
  //        Clockbase::changer.wait(expected_to_change);
  //        expected_to_change = !expected_to_change;
  //        auto curr_time = Clockbase::current_time.load();
  //        if (curr_time == 4400) {
  //           c++;
  //        }
  //     }
  // });



   play_interface(af);
   std::cin.get();
   stop_interface(af);

   // WavTool::writeWAV(44100, 
   //                   bounce1->duration, bounce1->buffer); 

   free(mem_devices.mem);

   // printf("4400 hits: %d\n", c);

   return 0;
}
