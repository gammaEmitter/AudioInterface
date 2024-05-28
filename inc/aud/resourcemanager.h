#pragma once
#include <memory>
#include "soundresource.h"
#include <unordered_map>

class ResourceManager {
public:
  static ResourceManager &getInstance() {
    static ResourceManager instance {};
    return instance;
  }

    void addWAV (const std::string& filename);
    std::shared_ptr<SoundRes> getFile (const std::string& filename);

private:
    ResourceManager() {}
    std::unordered_map<std::string, std::shared_ptr<SoundRes>> soundFiles;
    std::mutex mutex_;
};
