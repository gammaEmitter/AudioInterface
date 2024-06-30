

#include "audiointerface.h"
#include "iodef.h"
#include "portaudio.h"
#include <cstddef>
#include <fstream>
#include <ios>
#include <memory>
#include <pthread.h>
#include <string_view>
#include <utility>

static std::ofstream outfile {"testRecord.dat", std::ios::out};

AudioInterface::AudioInterface () {
    m_masterbus = std::make_unique<MasterBus>();
    m_ringbuffer = std::make_unique<Ringbuffer>();
    auto tmp = std::bind(&MasterBus::Out, m_masterbus.get());
    m_ringbuffer->set_source(tmp);
    err = Pa_Initialize();
    std::cout << err << std::endl;
    if (err ==  paNoError) {
        populateDevices();
    } else {
        std::cout << "Error initialising devices on hostapi " << Pa_GetDefaultHostApi()  << std::endl;
        
    }
    //  printDevices(std::cout); 
}

PaError AudioInterface::populateDevices() {
    PaError err;
    int num = Pa_GetDeviceCount();
    std::cout << num << std::endl;
    for (int i = 0; i < num; ++i) {
        m_devices[i] = Pa_GetDeviceInfo(i);

    }
    printDevices(std::cout);
    return err;
}

void AudioInterface::printDevices(std::ostream& outstream) { 
    std::ostringstream oss;
    for (auto& e : m_devices) {
        oss << "ID: [" << e.first << "]: " << e.second->name << std::endl; 
    }
    outstream << oss.str() << std::endl;
}
// pupolates stream information from the chosen device
void AudioInterface::populateOutStreamInfo() {
    if (m_odevice) {

        streaminfo.output_param.device = get_device(m_odevice);
        streaminfo.output_param.channelCount = AudIO::Mono;
        streaminfo.output_param.sampleFormat = paFloat32;
        streaminfo.output_param.suggestedLatency = m_odevice->defaultLowOutputLatency;
        streaminfo.output_param.hostApiSpecificStreamInfo = NULL;
    }
}
// pupolates stream information from the chosen device
void AudioInterface::populateInStreamInfo() {
    if (m_idevice) {
        streaminfo.input_param.device = get_device(m_idevice);
        streaminfo.input_param.channelCount = AudIO::Mono;
        streaminfo.input_param.sampleFormat = paFloat32;
        streaminfo.input_param.suggestedLatency = m_idevice->defaultLowInputLatency;
        streaminfo.input_param.hostApiSpecificStreamInfo = NULL;
    }
}

AudioInterface& AudioInterface::set_OutDevice(const std::string_view name) {
    for (auto dev : m_devices) {
        if (dev.second->name == name) {
            m_odevice = dev.second;
        }
    }
    populateOutStreamInfo();
    return *this;
}

AudioInterface& AudioInterface::set_OutDevice (PaDeviceIndex index) {
    m_odevice = Pa_GetDeviceInfo(index);
    populateOutStreamInfo();
    return *this;
}
AudioInterface& AudioInterface::set_InDevice(const std::string_view name) {
    for (auto dev : m_devices) {
        if (dev.second->name == name) {
            m_idevice = dev.second;
        }
    }
    populateInStreamInfo();
    return *this;
}
AudioInterface& AudioInterface::set_InDevice (PaDeviceIndex index) {
    m_idevice = Pa_GetDeviceInfo(index);
    populateInStreamInfo();
    return *this;
}


PaDeviceIndex AudioInterface::get_device(const PaDeviceInfo* name) const {
    for (auto& entry : m_devices) {
        if (entry.second == name)
            return entry.first;
    }
    return -1;
}


const PaDeviceInfo* AudioInterface::get_device (PaDeviceIndex index) const {
    for (auto& entry : m_devices) {
        if (entry.first == index)
            return entry.second;
    }
    return nullptr;
}

int AudioInterface::inOutCallback (const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData) {

    Ringbuffer* rb = (Ringbuffer*)userData;
    const float* rptr = (const float*)inputbuffer;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i++) {
        *write_ptr++ = rb->pull() + ((inputbuffer) ? AudIO::SampleSilence : *rptr++); 
    }
    return paContinue;
}


 int AudioInterface::outputCallback (const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData
        ) {
    Ringbuffer* rb = (Ringbuffer*) userData;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i += 16) {
        for (int j = 0; j < 16; ++j) {
            *write_ptr++ = rb->pull();
            Clockbase::increment();
        }
    } 
    return paContinue;
}

 int AudioInterface::writeOutputCallback (const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData
        ) {
    Ringbuffer* rb = (Ringbuffer*) userData;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i += 16) {
        for (int j = 0; j < 16; ++j) {
            float out = rb->pull();
            *write_ptr++ = out;
            outfile << out << "\n";
            Clockbase::increment();
        }
    } 
    return paContinue;
}


PaError AudioInterface::play() {
    streaminfo.err_status = Pa_OpenStream(&streaminfo.stream,
                NULL,
                &streaminfo.output_param,
                Clockbase::samplerate,
                AudIO::RingbufferSize / 4,
                paClipOff,
                outputCallback,
                (void*)m_ringbuffer.get());
    if (streaminfo.err_status != paNoError) {
        printf("Opening stream failed, Code %d \n", streaminfo.err_status);
    }
    //m_bufferservice->startTransfer();
    printf("Stream opened successfully on device %s \n", m_odevice->name);
    
    streaminfo.err_status = Pa_StartStream(streaminfo.stream);
    if (streaminfo.err_status != paNoError) {
        printf("Starting  stream failed, Code %d \n", streaminfo.err_status);
    }
    printf("Stream started successfully on device %s \n", m_odevice->name);


    return paNoError ;
    
}
PaError AudioInterface::play_writeToFile() {
    streaminfo.err_status = Pa_OpenStream(&streaminfo.stream,
                NULL,
                &streaminfo.output_param,
                Clockbase::samplerate,
                AudIO::RingbufferSize / 4,
                paClipOff,
                writeOutputCallback,
                (void*)m_ringbuffer.get());
    if (streaminfo.err_status != paNoError) {
        printf("Opening stream failed, Code %d \n", streaminfo.err_status);
    }
    //m_bufferservice->startTransfer();
    printf("Stream opened successfully on device %s \n", m_odevice->name);
    
    streaminfo.err_status = Pa_StartStream(streaminfo.stream);
    if (streaminfo.err_status != paNoError) {
        printf("Starting  stream failed, Code %d \n", streaminfo.err_status);
    }
    printf("Stream started successfully on device %s \n", m_odevice->name);


    return paNoError ;
    
}

MasterBus* AudioInterface::master() {
    return m_masterbus.get();
}
