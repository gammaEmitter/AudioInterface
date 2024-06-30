//

#include "bus.h"
#include "channel_audio.h"
#include "channel_midi.h"
#include "iodef.h"
#include <memory>

ChannelMidi*  Bus::add_channel_midi () {
//   m_channel = std::make_unique<Channel>();
    sources.push_back(std::make_unique<ChannelMidi>());
    return static_cast<ChannelMidi*>(sources.back().get());
}
ChannelAudio* Bus::add_channel_audio() {
    sources.push_back(std::make_unique<ChannelAudio>());
    return static_cast<ChannelAudio*>(sources.back().get());
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

