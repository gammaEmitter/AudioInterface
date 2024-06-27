set(SRCS 
    adsr.cpp
    audiointerface.cpp
    audioevent.cpp
    audioeventqueue.cpp
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

#target_sources(audiointerface PRIVATE ${SRCS})
add_library(audiocomponents ${SRCS})
