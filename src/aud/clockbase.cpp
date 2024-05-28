#include "clockbase.h"

    std::atomic<Timestamp_t>        Clockbase::current_time    = 0;

    std::atomic<size_t>             Clockbase::samples_passed  = 0;     // 0 - 44100

    SampleRate_t                    Clockbase::samplerate      = AudIO::Samplerate44100;
    
    uint8_t                         Clockbase::tempo           = 150;
