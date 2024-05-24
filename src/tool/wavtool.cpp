#include "wavtool.h"
#include <vector>

namespace WavTool {

uint32_t readUint32LE(std::ifstream &file) {
  uint8_t bytes[4];
  file.read(reinterpret_cast<char *>(bytes), 4);
  return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
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

uint16_t readUint16LE(std::ifstream &file) {
  uint8_t bytes[2];
  file.read(reinterpret_cast<char *>(bytes), 2);
  return (bytes[1] << 8) | bytes[0];
}

std::vector<float> getDataFloat(const RiffWAV &wav) {
  std::vector<float> conv{};
  size_t data_size = wav.data.size();
  conv.resize(data_size);
  float maxAmplitude = (float)pow(2, wav.bitsPerSample - 1) - 1;
  for (int i = 0; i < data_size; ++i) {
    conv[i] = wav.data[i] / maxAmplitude;
  }
  return conv;
}

void writeToFile(std::ofstream &file, int value, int size) {
  file.write(reinterpret_cast<const char *>(&value), size);
}

RiffWAV readWAV(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file");
  }

  RiffWAV wav;

  // Read the RIFF header
  wav.chunkID = readUint32LE(file);
  wav.chunkSize = readUint32LE(file);
  wav.format = readUint32LE(file);
  if (wav.chunkID != ChunkID::RIFF_LE ||
      wav.format != ChunkID::WAVE_LE) { // 'RIFF' and 'WAVE' in little-endian
    throw std::runtime_error("Invalid WAV file format");
  }

  // Read the fmt subchunk
  wav.subchunk1ID = readUint32LE(file);

  if (wav.subchunk1ID != ChunkID::FMT_LE) {
    if (wav.subchunk1ID == ChunkID::JUNK_LE) {
      printf("JUNK subchunk found\n");
      wav.junkID = ChunkID::JUNK_LE;
      wav.junkSize = readUint32LE(file);
      file.ignore(wav.junkSize);
      wav.subchunk1ID = readUint32LE(file);
    } else {
      throw std::runtime_error(
          "FMT subchunk not found\nJUNK subchunk not found");
    }
  }

  wav.subchunk1Size = readUint32LE(file);
  wav.audioFormat = readUint16LE(file);
  wav.numChannels = readUint16LE(file);
  wav.sampleRate = readUint32LE(file);
  wav.byteRate = readUint32LE(file);
  wav.blockAlign = readUint16LE(file);
  wav.bitsPerSample = readUint16LE(file);

  // Read the data subchunk
  wav.subchunk2ID = readUint32LE(file);
  wav.subchunk2Size = readUint32LE(file);

  if (wav.subchunk2ID != ChunkID::DATA_LE) {
    throw std::runtime_error("Data subchunk not found");
  }
  // Read the audio data
  int numSamples = wav.subchunk2Size / (wav.bitsPerSample / 8);
  wav.data.resize(numSamples);

  for (int i = 0; i < numSamples; ++i) {
    if (wav.bitsPerSample == 16) {
      wav.data[i] = readUint16LE(file);
    } else if (wav.bitsPerSample == 24) {
      wav.data[i] = readUint24LE(file);
    } else if (wav.bitsPerSample == 32) {
      wav.data[i] = readUint32LE(file);
    } else {
      throw std::runtime_error("Unsupported Bits per Sample!");
    }
  }

  return wav;
}

void writeWAV(int sr, int duration, const std::vector<float> &data) {
  int kCh = 1;
  int bitD = 24;
  std::ofstream audioFile;
  audioFile.open("waveform.wav", std::ios::binary);

  // Header Chunk of WAV File Format --> see WAVE Format Documentation
  audioFile << "RIFF";
  audioFile << "----"; // Platzhalter für 'size of file' 4 Bytes
  audioFile << "WAVE";

  // Format Chunk
  audioFile << "fmt ";
  writeToFile(audioFile, 16, 4);                  // Size of format chunk
  writeToFile(audioFile, 1, 2);                   // Comperssion Codee
  writeToFile(audioFile, 1, 2);                   // Number of Channels
  writeToFile(audioFile, sr, 4);                  // Samplerate
  writeToFile(audioFile, kCh * sr * bitD / 8, 4); // ByteRate
  writeToFile(audioFile, kCh * bitD / 8, 2);      // BlockAlign
  writeToFile(audioFile, bitD, 2);                // BitsPerSample

  // Data Chunk
  audioFile << "data";
  audioFile << "----";
  int preAudioPosition = audioFile.tellp();
  auto maxAmplitude = pow(2, bitD - 1) - 1;
  for (int i = 0; i < sr * duration; i++) { // Samples schreiben
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
