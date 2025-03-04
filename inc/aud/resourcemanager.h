#pragma once
#include "wavtool.h"
#include <memory>
#include <unordered_map>

struct SoundRes {
  enum Type {
    WAV,
    FLAC,
  };
  Type type;
  union data {
    WavTool::RiffWAV* wav;
  } data;
};

class ResourceManager {
public:
  static ResourceManager &getInstance() {
    static ResourceManager instance {};
    return instance;
  }

    SoundRes* addWAV(AAllocator& alloc, const std::string& filename);
    SoundRes* getFile (const std::string& filename);

private:
    ResourceManager() {}
    std::unordered_map<std::string, SoundRes> soundFiles;
    std::mutex mutex_;
};
