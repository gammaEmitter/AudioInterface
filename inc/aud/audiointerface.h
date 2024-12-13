#pragma once
//
//
#include "audioeventmap.h"
#include "clockbase.h"
#include "iodef.h"
#include "mixer.h"
#include "portaudio.h"
#include "ringbuffer.h"
#include <algorithm>
#include <map>
#include <sstream>
#include <string_view>

struct StreamParameters {

  PaStreamParameters input_param, output_param;
  PaStream *stream;
  PaError err_status;
};

struct AudioInterface {

  Mixer* mixer {};


  std::map<PaDeviceIndex, const PaDeviceInfo *> devices{};
  PaError err = paNoError;
  StreamParameters streaminfo;

  const PaDeviceInfo *odevice;
  const PaDeviceInfo *idevice;
};

void printDevices(AudioInterface &, std::ostream &);

PaError play_interface(AudioInterface &aud);
PaError stop_interface(AudioInterface &aud);

AudioInterface &init_audio_interface(AudioInterface &);
PaError populateDevices(AudioInterface &);
AudioInterface &populateOutStreamInfo(AudioInterface &);
AudioInterface &populateInStreamInfo(AudioInterface &);
const PaDeviceIndex get_device(AudioInterface &, const PaDeviceInfo *);
AudioInterface &set_odevice(AudioInterface &, PaDeviceIndex);
AudioInterface &set_idevice(AudioInterface &, PaDeviceIndex);

static int outputCallback(const void *inputbuffer, void *outputbuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeinfo,
                          PaStreamCallbackFlags statusflags, void *userData);
