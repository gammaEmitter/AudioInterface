#include "tool/wavtool.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (!argv[1]) return -1;
    try {
        std::string file  = argv[1];
        WavTool::RiffWAV wav = WavTool::readWAV(file);
        std::cout << "File read successfully!" << std::endl;
        std::cout << "Sample Rate: " << wav.sampleRate << std::endl;
        std::cout << "Audio Format: " << wav.audioFormat << std::endl;
        std::cout << "Bits: " << wav.bitsPerSample << std::endl;
        std::cout << "Number of Channels: " << wav.numChannels << std::endl;
        std::cout << "Data Size: " << wav.data.size() << " samples" << std::endl;
        std::cout << "Duration: " << ((float) wav.data.size() / (float) wav.sampleRate) << " seconds" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
