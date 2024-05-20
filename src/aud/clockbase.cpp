#include "clockbase.h"


    std::atomic<size_t>             Clockbase::ticks          = 0;           // 0 - 63 
    std::atomic<uint32_t>           Clockbase::seconds        = 0;           // counts up


    uint32_t                        Clockbase::counter       = 0;            // 0 - m_period
    size_t                          Clockbase::tickphase     = 0;            // 0 - 3
    Clockbase::TickPeriod_44        Clockbase::period        = standard;

