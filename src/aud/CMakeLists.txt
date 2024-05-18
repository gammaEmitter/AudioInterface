set(SRCS 
    audiointerface.cpp
    bus.cpp
    bufferservice.cpp
    channel.cpp
    ringbuffer.cpp
    oscillator.cpp
    wavetable.cpp
    wtoscillator.cpp
    )

target_sources(audiointerface PRIVATE ${SRCS})
add_library(audiocomponents ${SRCS})
