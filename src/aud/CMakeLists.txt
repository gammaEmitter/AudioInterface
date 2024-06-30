set(SRCS 
    adsr.cpp
    audiointerface.cpp
    audioevent.cpp
    audioeventqueue.cpp
    bus.cpp
    channel_audio.cpp
    midieventqueue.cpp
    channel_midi.cpp
    ringbuffer.cpp
    clockbase.cpp
    metronome.cpp
    midimessaging.cpp
    oscillator.cpp
    resourcemanager.cpp
    wavetable.cpp
    wtoscillator.cpp
    )

#target_sources(audiointerface PRIVATE ${SRCS})
add_library(audiocomponents ${SRCS})
