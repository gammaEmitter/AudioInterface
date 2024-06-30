#pragma once
//
//
#include <algorithm>
#include <map>
#include <sstream>
#include <string_view>
#include "portaudio.h"
#include "ringbuffer.h"
#include "bus.h"
#include "iodef.h"
#include "clockbase.h"


class AudioInterface {
    
    public:
        AudioInterface ();
        ~AudioInterface() = default;
        AudioInterface(AudioInterface& other) = delete;
        AudioInterface& operator=(AudioInterface& other) = delete;
        AudioInterface (AudioInterface&& other) = delete;
        AudioInterface& operator=(AudioInterface&& other) = delete;

        AudioInterface& set_OutDevice(const std::string_view name);
        AudioInterface& set_OutDevice (PaDeviceIndex index);
        AudioInterface& set_InDevice(const std::string_view name);
        AudioInterface& set_InDevice (PaDeviceIndex index);
        PaDeviceIndex  get_device(const PaDeviceInfo* name) const ;
        const PaDeviceInfo*  get_device (PaDeviceIndex index) const;
        MasterBus* master ();
        PaError play();
        PaError play_writeToFile();

        struct StreamParameters {
            
                PaStreamParameters input_param,
                                   output_param;
                PaStream*          stream;
                PaError            err_status;

        };

    private:
        PaError populateDevices();
        void printDevices(std::ostream& outstream);
        void populateOutStreamInfo();
        void populateInStreamInfo();


        static int  inOutCallback (const void* inputbuffer, 
                                void* outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeinfo,
                                PaStreamCallbackFlags statusflags,
                                void* userData
        );
        static int  outputCallback (const void* inputbuffer, 
                                void* outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeinfo,
                                PaStreamCallbackFlags statusflags,
                                void* userData
        );
        static int  writeOutputCallback (const void* inputbuffer, 
                                void* outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeinfo,
                                PaStreamCallbackFlags statusflags,
                                void* userData
        );
        std::map<PaDeviceIndex, const PaDeviceInfo* >       m_devices {};
        std::unique_ptr<MasterBus>                          m_masterbus = nullptr;
        std::unique_ptr<Ringbuffer>                         m_ringbuffer = nullptr;
        PaError                                             err = paNoError;
        StreamParameters                                    streaminfo;
        const PaDeviceInfo*                                 m_odevice;
        const PaDeviceInfo*                                 m_idevice;
};




