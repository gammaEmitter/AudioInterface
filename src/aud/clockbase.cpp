#include "clockbase.h"

    std::atomic<Timestamp_t>        Clockbase::current_time     = 0;

    std::atomic<size_t>             Clockbase::samples_passed   = 0;     // 0 - 44100

    SampleRate_t                    Clockbase::samplerate       = AudIO::Samplerate44100;
    
    uint8_t                         Clockbase::tempo            = 150;

    bool                            Clockbase::loop_active      = false;

    bool                            Clockbase::loop_pivot       = false;

    Timestamp_t                     Clockbase::loop_in          = 0;

    Timestamp_t                     Clockbase::loop_out         = 44100;

/*
 *  Creates a Timestamp from a position in th beat-grid
 *   Ticks range from 0 to 63
 */
Timestamp_t timeFromBeats(uint16_t beats, uint8_t ticks) {

    int tick64_length = Clockbase::beat_length() / 64;
    Timestamp_t time = (beats * Clockbase::beat_length()) + (ticks * tick64_length);
    return time;
}
BeatUnit beatsFromTime(Timestamp_t time) {
    BeatUnit res {};
    uint16_t beatlen =  Clockbase::beat_length();
    res.beats = time / beatlen;
    int tick64_length = beatlen / 64;
    res.ticks = (time % beatlen) / tick64_length;  
    return res;
}
