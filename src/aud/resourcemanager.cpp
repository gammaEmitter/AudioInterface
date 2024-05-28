#include "resourcemanager.h"
#include "wavtool.h"


std::shared_ptr<SoundRes> ResourceManager::addWAV(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    WavTool::RiffWAV wav = WavTool::readWAV(filename);
    auto soundFile = std::make_shared<SoundRes>(wav);
    soundFiles[filename] = soundFile;
    return soundFile;
}

std::shared_ptr<SoundRes> ResourceManager::getFile (const std::string& filename) {

    std::lock_guard<std::mutex> lock(mutex_);
    auto it = soundFiles.find(filename);
    if (it != soundFiles.end()) {
        return it->second;
    }
    return std::make_shared<SoundRes> ();
}
