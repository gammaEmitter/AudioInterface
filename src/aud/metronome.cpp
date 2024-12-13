#include "metronome.h"

void init_metronome (Metronome& metr, std::string& file_name) {
   metr.wav = WavTool::readWAV(file_name);
}
