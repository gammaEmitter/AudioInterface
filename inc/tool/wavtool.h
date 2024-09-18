#pragma once
#include <vector>
#include <fstream>
#include <stdint.h>

namespace WavTool {

enum ChunkID {
    RIFF_LE = 0x46464952,
    WAVE_LE = 0x45564157,
    JUNK_LE = 0x4b4e554A,
    FMT_LE = 0x20746d66,
    DATA_LE = 0x61746164,
};

struct RiffWAV {
    // RIFF Header
    uint32_t chunkID {};
    uint32_t chunkSize {};
    uint32_t format {};
    //junk optional
    uint32_t junkID {};
    uint32_t junkSize {};
    
    // fmt
    uint32_t subchunk1ID {};
    uint32_t subchunk1Size {};
    uint16_t audioFormat {};
    uint16_t numChannels {};
    uint32_t sampleRate {};
    uint32_t byteRate {};
    uint16_t blockAlign {};
    uint16_t bitsPerSample {};
    ///// for pcm this doesnt exist. keep an eye on http://soundfile.sapp.org/doc/WaveFormat/
    // data
    uint32_t subchunk2ID {};
    uint32_t subchunk2Size {};
    std::vector<float> data {};
};

RiffWAV readWAV(const std::string &filename);
void writeWAV (int sr, int duration, const std::vector<float>& data);
std::vector<float> PCMtoFloat(const std::vector<int32_t>& wav, uint8_t bitdepth);

}

