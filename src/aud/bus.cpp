//

#include "bus.h"
#include "iodef.h"
#include <memory>

Channel*  Bus::add_channel () {
//   m_channel = std::make_unique<Channel>();
    sources.push_back(std::make_unique<Channel>());
    return sources.back().get();
    
}

std::vector<Channel*> Bus::channels(){
    //return m_channel.get();
    std::vector<Channel*> res;
    for (auto& ch_ptr : sources) {
        res.push_back(ch_ptr.get());
    }
    return res;
}

float Bus::Out() {
    // add filter, effects mechanics
    //fmt::print("Bus.Out()\n");
    float tmp = AudIO::SampleSilence;
    for (auto& ch_ptr : sources) {
        tmp += ch_ptr->Out(); 
        if (tmp > 1) return 1.f;
        if (tmp < -1) return -1.f;
        
    }
    /*    if (m_channel) {
        tmp += m_channel->Out(); 
        if (tmp > 1) return 1.f;
        if (tmp < -1) return -1.f;
    }
*/
    return tmp; 
}

