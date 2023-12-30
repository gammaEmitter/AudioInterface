#pragma once
//
//
#include <algorithm>
#include <map>
#include <sstream>
#include "bufferservice.h"
#include "portaudio.h"
#include "ringbuffer.h"
#include "bus.h"
#include "iodef.h"


class AudioInterface {
    
    public:
        AudioInterface ();
        ~AudioInterface() = default;
        AudioInterface(AudioInterface& other) = delete;
        AudioInterface& operator=(AudioInterface& other) = delete;
        AudioInterface (AudioInterface&& other) = delete;
        AudioInterface& operator=(AudioInterface&& other) = delete;

        AudioInterface& set_OutDevice(const PaDeviceInfo* name);
        AudioInterface& set_OutDevice (PaDeviceIndex index);
        AudioInterface& set_InDevice(const PaDeviceInfo* name);
        AudioInterface& set_InDevice (PaDeviceIndex index);
        PaDeviceIndex  get_device(const PaDeviceInfo* name) const ;
        const PaDeviceInfo*  get_device (PaDeviceIndex index) const;
        AudioInterface& add_channel ();
        MasterBus* master ();
        PaError play();
        PaError record();

        struct StreamParameters {
            
                PaStreamParameters input_param,
                                   output_param;
                PaStream*          stream;
                PaError            err_status;

        };

    private:
        friend void* _Play(void* args);
        PaError populateDevices();
        void printDevices(std::ostream& outstream);
        void populateOutStreamInfo();
        void populateInStreamInfo();


        static int  outputCallback (const void* inputbuffer, 
                                void* outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeinfo,
                                PaStreamCallbackFlags statusflags,
                                void* userData
        );
        static int  inputCallback (const void* inputbuffer, 
                                void* outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeinfo,
                                PaStreamCallbackFlags statusflags,
                                void* userData
        );
        std::map<PaDeviceIndex, const PaDeviceInfo* > m_devices;
        std::unique_ptr<MasterBus> m_masterbus = nullptr;
        std::unique_ptr<BufferService> m_bufferservice = nullptr;
        std::unique_ptr<Ringbuffer> m_ringbuffer = nullptr;
        PaError err;
        StreamParameters streaminfo;
        const PaDeviceInfo* m_odevice;
        const PaDeviceInfo* m_idevice;
};




