#include "metronome.h"

void Metronome::on() {}

void Metronome::off() {}

void Metronome::loadFile() {
    WavTool::RiffWAV tock = WavTool::readWAV(file_name);
    audio_data = WavTool::getDataFloat(tock);

}
