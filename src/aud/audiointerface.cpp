

#include "audiointerface.h"
#include "iodef.h"
#include "portaudio.h"
#include <__chrono/duration.h>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <ios>
#include <memory>
#include <pthread.h>
#include <string_view>
#include <utility>

//static std::ofstream outfile {"testRecord.dat", std::ios::out};
AudioInterface& init_audio_interface(AudioInterface& aud) {
    aud.err = Pa_Initialize();
    std::cout << "PortAudio initialization  " << ((aud.err) ? "failed" : "succeeded") << std::endl;
    if (aud.err ==  paNoError) {
        populateDevices(aud);
    } else {
        std::cout << "Error initialising devices on hostapi " << Pa_GetDefaultHostApi()  << std::endl;
    }
     printDevices(aud, std::cout); 
    return aud;
}

PaError populateDevices(AudioInterface& aud) {
    PaError err;
    int num = Pa_GetDeviceCount();
    std::cout << num << " Devices found"<< std::endl;
    for (int i = 0; i < num; ++i) {
        aud.devices[i] = Pa_GetDeviceInfo(i);

    }
    return err;
}

void printDevices(AudioInterface& aud, std::ostream& outstream) { 
    std::ostringstream oss;
    for (auto& e : aud.devices) {
        oss << "ID: [" << e.first << "]: " << e.second->name << std::endl; 
    }
    outstream << oss.str() << std::endl;
}
// pupolates stream information from the chosen device
AudioInterface& populateOutStreamInfo(AudioInterface& aud) {
    if (aud.odevice) {
        aud.streaminfo.output_param.device = get_device(aud, aud.odevice);
        // aud.streaminfo.output_param.channelCount = AudIO::Mono;
        aud.streaminfo.output_param.channelCount = (aud.odevice->maxOutputChannels > 1) ?  AudIO::Stereo : AudIO::Mono;
        aud.streaminfo.output_param.sampleFormat = paFloat32;
        aud.streaminfo.output_param.suggestedLatency = aud.odevice->defaultLowOutputLatency;
        aud.streaminfo.output_param.hostApiSpecificStreamInfo = NULL;
    }
    return aud;
}
// pupolates stream information from the chosen device
AudioInterface& populateInStreamInfo(AudioInterface& aud) {
    if (aud.idevice) {
        aud.streaminfo.input_param.device = get_device(aud, aud.idevice);
        aud.streaminfo.input_param.channelCount = AudIO::Mono;
        aud.streaminfo.input_param.sampleFormat = paFloat32;
        aud.streaminfo.input_param.suggestedLatency = aud.idevice->defaultLowInputLatency;
        aud.streaminfo.input_param.hostApiSpecificStreamInfo = NULL;
    }
    return aud;
}

AudioInterface& set_odevice (AudioInterface& aud, PaDeviceIndex index) {
    aud.odevice = Pa_GetDeviceInfo(index);
    populateOutStreamInfo(aud);
    return aud;
}
AudioInterface& set_idevice (AudioInterface& aud, PaDeviceIndex index) {
    aud.idevice = Pa_GetDeviceInfo(index);
    populateInStreamInfo(aud);
    return aud;
}


const PaDeviceIndex get_device(AudioInterface& aud, const PaDeviceInfo* name) {
    for (auto& entry : aud.devices) {
        if (entry.second == name)
            return entry.first;
    }
    return -1;
}

 int outputCallbackMono(const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData
        ) {
    auto start = std::chrono::high_resolution_clock::now(); 
    Mixer* mixer = (Mixer*) userData;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i += 16) {
        for (int j = 0; j < 16; ++j) {
            *write_ptr++ = sum_mixer(mixer);
            Clockbase::increment();
        }
    } 
    auto end = std::chrono::high_resolution_clock::now(); 
    printf("Out() Chain Time for %lu samples: %lld\n",framesPerBuffer, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    return paContinue;
}
 int outputCallbackStereo(const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData
        ) {
    // auto start = std::chrono::high_resolution_clock::now(); 
    Mixer* mixer = (Mixer*) userData;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i += 16) {
        for (int j = 0; j < 16; ++j) {
            *write_ptr++ = sum_mixer(mixer);
            *write_ptr++ = sum_mixer(mixer);
            Clockbase::increment();
        }
    } 
    // auto end = std::chrono::high_resolution_clock::now(); 
    // printf("Out() Chain Time for %lu samples: %lld\n",framesPerBuffer, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
    return paContinue;
}


PaError play_interface(AudioInterface& aud) {

    aud.streaminfo.err_status = Pa_OpenStream(&aud.streaminfo.stream,
                NULL,
                &aud.streaminfo.output_param,
                Clockbase::samplerate,
                AudIO::RingbufferSize,
                paClipOff,
                (aud.streaminfo.output_param.channelCount == 2) ? outputCallbackStereo : outputCallbackMono,
                (void*)aud.mixer);
    if (aud.streaminfo.err_status != paNoError) {
        printf("Opening stream failed, Code %d \n", aud.streaminfo.err_status);
    }
    //m_bufferservice->startTransfer();
    printf("Stream opened successfully on device %s \n", aud.odevice->name);
    
    aud.streaminfo.err_status = Pa_StartStream(aud.streaminfo.stream);
    if (aud.streaminfo.err_status != paNoError) {
        printf("Starting  stream failed, Code %d \n", aud.streaminfo.err_status);
    }
    printf("Stream started successfully on device %s \n", aud.odevice->name);


    return paNoError ;
    
}

PaError stop_interface(AudioInterface &aud) {
    return Pa_StopStream(aud.streaminfo.stream);
}




