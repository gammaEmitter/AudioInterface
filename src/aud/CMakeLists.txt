set(SRCS 
    adsr.cpp
    audiointerface.cpp
    audioevent.cpp
    audioeventmap.cpp
    bus.cpp
    channel_audio.cpp
    midievent.cpp
    midieventmap.cpp
    channel_midi.cpp
    ringbuffer.cpp
    clockbase.cpp
    metronome.cpp
    oscillator.cpp
    resourcemanager.cpp
    wavetable.cpp
    wtoscillator.cpp
    )

#target_sources(audiointerface PRIVATE ${SRCS})
add_library(audiocomponents ${SRCS})
