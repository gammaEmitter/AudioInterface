#include "resourcemanager.h"
#include "allocator.h"
#include "wavtool.h"


SoundRes* ResourceManager::addWAV(AAllocator& alloc, const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    WavTool::RiffWAV* wav = WavTool::readWAV(alloc, filename);
    soundFiles[filename] = SoundRes {SoundRes::WAV, {wav}};
    return &soundFiles[filename];
}

SoundRes* ResourceManager::getFile (const std::string& filename) {

    std::lock_guard<std::mutex> lock(mutex_);
    auto it = soundFiles.find(filename);
    if (it != soundFiles.end()) {
        return &(it->second);
    }
    return nullptr;
}
