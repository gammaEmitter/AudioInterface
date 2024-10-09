#include "wtoscillator.h"


WaveTableOscillator::WaveTableOscillator(WaveTableStrategy_fn waveform,  float frequency) { 
   m_wavetable = std::make_unique<WaveTable>(waveform, frequency);
   m_frequency = frequency;
   // out_fn = std::bind(&WaveTableOscillator::Out, *this);
   //
   // funktioniert das?? oder ergibt das nullptr? capturing this ergibt eine std::function ??
   out_fn = [this](){return Out();};

}

