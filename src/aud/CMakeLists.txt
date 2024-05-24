set(SRCS 
    audiointerface.cpp
    bus.cpp
    bufferservice.cpp
    channel.cpp
    ringbuffer.cpp
    clockbase.cpp
    metronome.cpp
    oscillator.cpp
    wavetable.cpp
    wtoscillator.cpp
    )

target_sources(audiointerface PRIVATE ${SRCS})
add_library(audiocomponents ${SRCS})
