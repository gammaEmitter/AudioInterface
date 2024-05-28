set(SRCS 
    audiointerface.cpp
    audioevent.cpp
    bus.cpp
    bufferservice.cpp
    channel.cpp
    ringbuffer.cpp
    clockbase.cpp
    metronome.cpp
    oscillator.cpp
    resourcemanager.cpp
    wavetable.cpp
    wtoscillator.cpp
    )

target_sources(audiointerface PRIVATE ${SRCS})
#add_library(audiocomponents ${SRCS})
