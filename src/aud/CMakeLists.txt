set(SRCS 
    adsr.cpp
    allocator.cpp
    audiointerface.cpp
    audioevent.cpp
    audioeventmap.cpp
    filter/biquad.cpp
    filter/delay.cpp
    midievent.cpp
    midieventmap.cpp
    mixer.cpp
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
