#include "wavtool.h"
#include "allocator.h"
#include <fstream>
#include <vector>

namespace WavTool {

int32_t readUint32LE(std::ifstream &file) {
  uint8_t bytes[4];
  file.read(reinterpret_cast<char *>(bytes), 4);
  int32_t result = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];

  if (result & 0x80000000) {
    result |= ~0xFFFFFFFF;
  }
  return result;
}
int32_t readUint24LE(std::ifstream &file) {
  uint8_t bytes[3];
  file.read(reinterpret_cast<char *>(bytes), 3);
  // Convert to 32-bit signed integer
  int32_t result = (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
  // Sign-extend if necessary
  if (result & 0x800000) {
    result |= ~0xFFFFFF;
  }
  return result;
}

int16_t readUint16LE(std::ifstream &file) {
  uint8_t bytes[2];
  file.read(reinterpret_cast<char *>(bytes), 2);
  int16_t result = (bytes[1] << 8) | bytes[0];


  if (result & 0x8000) {
    result |= ~0xFFFF;
  }

  return result; 
}

void PCMtoFloat(int32_t* pcm, float* wav, size_t len,uint8_t bitdepth) {
  float maxAmplitude = (float)pow(2, bitdepth - 1) - 1;
  for (int i = 0; i < len; ++i) {
    wav[i] = wav[i] / maxAmplitude;
  }
  return;
}

void writeToFile(std::ofstream &file, int value, int size) {
  file.write(reinterpret_cast<const char *>(&value), size);
}

RiffWAV* readWAV(AAllocator& alloc, const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file " + filename);
  }

  RiffWAV* wav = (RiffWAV*) allocate_aa(alloc, sizeof(RiffWAV));

  // Read the RIFF header
  wav->chunkID = readUint32LE(file);
  wav->chunkSize = readUint32LE(file);
  wav->format = readUint32LE(file);
  if (wav->chunkID != ChunkID::RIFF_LE ||
      wav->format != ChunkID::WAVE_LE) { // 'RIFF' and 'WAVE' in little-endian
    throw std::runtime_error("Invalid WAV file format");
  }

  while(file) {
    uint32_t chunkID = readUint32LE(file); 
    uint32_t chunkSize = readUint32LE(file);

    switch(chunkID) {

      case ChunkID::JUNK_LE:

        wav->junkID = ChunkID::JUNK_LE;
        wav->junkSize = chunkSize;
        file.ignore(wav->junkSize);
        break;

      case ChunkID::FMT_LE:

        wav->subchunk1ID = ChunkID::FMT_LE;
        wav->subchunk1Size = chunkSize;
        wav->audioFormat = readUint16LE(file);
        wav->numChannels = readUint16LE(file);
        wav->sampleRate = readUint32LE(file);
        wav->byteRate = readUint32LE(file);
        wav->blockAlign = readUint16LE(file);
        wav->bitsPerSample = readUint16LE(file);
        // Skip any extra parameters in the fmt subchunk
        if (wav->subchunk1Size > 16) {
          file.ignore(wav->subchunk1Size - 16);
        }
        break;
      
      case ChunkID::DATA_LE:
        {
          float maxAmplitude = (float)pow(2, wav->bitsPerSample - 1) - 1;

          wav->subchunk2ID = ChunkID::DATA_LE;
          wav->subchunk2Size = chunkSize;

          int numSamples = wav->subchunk2Size / (wav->bitsPerSample / 8);
          // wav.data.resize(numSamples);
          wav->data = (float*) allocate_aa(alloc, numSamples * sizeof(float));
          wav->len_data = numSamples;
          if ( wav->bitsPerSample != 16 && wav->bitsPerSample != 24 && wav->bitsPerSample != 32) {
            printf("Unsupported bit-depth: %d \n", wav->bitsPerSample);
            return nullptr;
          }
          if (wav->bitsPerSample == 16) {
            for (int i = 0; i < numSamples; ++i) {
                wav->data[i] = readUint16LE(file) / maxAmplitude;
            }
          }
          if (wav->bitsPerSample == 24) {
            for (int i = 0; i < numSamples; ++i) {
              wav->data[i] = readUint24LE(file) / maxAmplitude;
            }
          }
          if (wav->bitsPerSample == 32) {
            for (int i = 0; i < numSamples; ++i) {
                wav->data[i] = readUint32LE(file) / maxAmplitude;
            }
          }
          break;
        }

      default:
        file.ignore(chunkSize);
    }

  }
  file.close();
  return wav;
}

void writeWAV(int sr, int duration, float* data) {
  int kCh = 2;
  int bitD = 24;
  std::ofstream audioFile;
  audioFile.open("output_bounce.wav", std::ios::binary);

  // Header Chunk of WAV File Format --> see WAVE Format Documentation
  audioFile << "RIFF";
  audioFile << "----"; // Platzhalter für 'size of file' 4 Bytes
  audioFile << "WAVE";

  // Format Chunk
  audioFile << "fmt ";
  writeToFile(audioFile, 16, 4);                  // Size of format chunk
  writeToFile(audioFile, 1, 2);                   // Comperssion Codee
  writeToFile(audioFile, kCh, 2);                   // Number of Channels
  writeToFile(audioFile, sr, 4);                  // Samplerate
  writeToFile(audioFile, kCh * sr * bitD / 8, 4); // ByteRate
  writeToFile(audioFile, kCh * bitD / 8, 2);      // BlockAlign
  writeToFile(audioFile, bitD, 2);                // BitsPerSample

  // Data Chunk
  audioFile << "data";
  audioFile << "----";
  int preAudioPosition = audioFile.tellp();
  auto maxAmplitude = pow(2, bitD - 1) - 1;
  for (int i = 0; i < duration; i++) { // Samples schreiben
    auto sample = data[i];
    int intSample = static_cast<int>(sample * maxAmplitude);
    writeToFile(audioFile, intSample, bitD / 8);
  }

  int postAudioPosition = audioFile.tellp();

  audioFile.seekp(preAudioPosition - 4);
  writeToFile(audioFile, postAudioPosition - preAudioPosition, 4);

  audioFile.seekp(4, std::ios::beg);
  writeToFile(audioFile, postAudioPosition - 8, 4);

  audioFile.close();
}

} // namespace WavTool
