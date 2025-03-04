#include "metronome.h"
#include "allocator.h"

void init_metronome (Metronome& metr, AAllocator& alloc, std::string& file_name) {
   metr.wav = WavTool::readWAV(alloc, file_name);
}
