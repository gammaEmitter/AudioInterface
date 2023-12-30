

#include "audiointerface.h"
#include "bufferservice.h"
#include "iodef.h"
#include "portaudio.h"
#include <memory>
#include <pthread.h>
#include <utility>


AudioInterface::AudioInterface () {
    m_masterbus = std::make_unique<MasterBus>();
    m_ringbuffer = std::make_unique<Ringbuffer>();
    m_bufferservice = std::make_unique<BufferService>();
    auto tmp = std::bind(&MasterBus::Out, m_masterbus.get());
    m_bufferservice->setSource(tmp);
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
void AudioInterface::populateOutStreamInfo() {
    if (m_odevice) {

        streaminfo.output_param.device = get_device(m_odevice);
        streaminfo.output_param.channelCount = AudIO::Mono;
        streaminfo.output_param.sampleFormat = paFloat32;
        streaminfo.output_param.suggestedLatency = m_odevice->defaultLowInputLatency;
        streaminfo.output_param.hostApiSpecificStreamInfo = NULL;

    }
}
void AudioInterface::populateInStreamInfo() {
    if (m_idevice) {
        streaminfo.input_param.device = get_device(m_idevice);
        streaminfo.input_param.channelCount = AudIO::Mono;
        streaminfo.input_param.sampleFormat = paFloat32;
        streaminfo.input_param.suggestedLatency = m_idevice->defaultLowInputLatency;
        streaminfo.input_param.hostApiSpecificStreamInfo = NULL;

    }
}
// pupolates stream information from the chosen device
AudioInterface& AudioInterface::set_OutDevice(const PaDeviceInfo*  name) {
     m_odevice = name;
    populateOutStreamInfo();
    return *this;
}


// pupolates stream information from the chosen device
AudioInterface& AudioInterface::set_OutDevice (PaDeviceIndex index) {
    m_odevice = Pa_GetDeviceInfo(index);
    populateOutStreamInfo();
    return *this;
}
// pupolates stream information from the chosen device
AudioInterface& AudioInterface::set_InDevice(const PaDeviceInfo*  name) {
     m_idevice = name;
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

 int AudioInterface::outputCallback (const void* inputbuffer, 
        void* outputbuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeinfo,
        PaStreamCallbackFlags statusflags,
        void* userData
        ) {

    Ringbuffer* rb = (Ringbuffer*)userData;
    float* write_ptr = (float*) outputbuffer;
    for (size_t i = 0; i < framesPerBuffer; i++) {
        *write_ptr++ = rb->pull(); 
    }
    return paContinue;
}

int AudioInterface::inputCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    Ringbuffer* data = (Ringbuffer*)userData;
    const float *rptr = (const float*)inputBuffer; // read pointer zeigt auf InputBuffer, der von PortAudio gefüllt wird
    int write_index = data->write_index - 10; // write pointer zeigt auf die ausgegebenen daten am jeweiligen Index
    long i;
    int finished;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;


        finished = paContinue;

    if( inputBuffer == NULL) {
        for( i=0; i<framesPerBuffer; i++){
            data->operator[](write_index++) = AudIO::SampleSilence;  /* left */
        }
    }
    else {
        for( i=0; i<framesPerBuffer; i++ ) {
            data->operator[](write_index++) = *rptr++;  /* left */
        }
    }
    return finished;
}


PaError AudioInterface::play() {

    if (m_odevice) {
        streaminfo.err_status = Pa_OpenStream(&streaminfo.stream,
                &streaminfo.input_param,
                &streaminfo. output_param,
                m_odevice->defaultSampleRate,
                m_ringbuffer->capacity(),
                paClipOff,
                outputCallback,
                (void*)m_ringbuffer.get());
    }
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
PaError AudioInterface::record() {

    if (m_idevice) {
        streaminfo.err_status = Pa_OpenStream(&streaminfo.stream,
                NULL,
                &streaminfo. output_param,
                m_idevice->defaultSampleRate,
                m_ringbuffer->capacity(),
                paClipOff,
                inputCallback,
                (void*)m_ringbuffer.get());
    }
    if (streaminfo.err_status != paNoError) {
        printf("Opening stream failed, Code %d \n", streaminfo.err_status);
    }
    //m_bufferservice->startTransfer();
    printf("Stream opened successfully on device %s \n", m_idevice->name);
    
    streaminfo.err_status = Pa_StartStream(streaminfo.stream);
    if (streaminfo.err_status != paNoError) {
        printf("Starting  stream failed, Code %d \n", streaminfo.err_status);
    }
    printf("Stream started successfully on device %s \n", m_idevice->name);


    return paNoError ;
    
}


AudioInterface& AudioInterface::add_channel () {
    m_masterbus->add_channel();
    return *this;
}

MasterBus* AudioInterface::master() {
    return m_masterbus.get();
}
