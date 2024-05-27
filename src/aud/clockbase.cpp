#include "clockbase.h"
#include <cstddef>

    std::atomic<Timestamp_t>        Clockbase::current_time     = 0;

    std::atomic<size_t>             Clockbase::samples_passed   = 0;           // 0 - (sammplerate - 1)
    std::atomic<uint8_t>            Clockbase::time_ticks       = 0;           // 0 - 63 
    std::atomic<uint16_t>           Clockbase::seconds          = 0;           // counts up

    std::atomic<uint8_t>            Clockbase::tempo_ticks      = 0;           // 0 - 63 
    std::atomic<uint16_t>             Clockbase::beats            = 0;

    uint8_t                         Clockbase::tempo            = 120;

    uint16_t                        Clockbase::counter          = 0;            // 0 - m_period
    uint8_t                         Clockbase::tickphase        = 0;            // 0 - 3
    Clockbase::TickPeriod_44        Clockbase::period           = standard;
    size_t                          Clockbase::tempo_period     = Clockbase::period \
                                                                  * (60/Clockbase::tempo);

