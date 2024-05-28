#pragma once
#include <cmath>
#include <vector>
#include <functional>
#include <concepts>
#include <array>
#include <queue>
#include <memory>


namespace AudIO {

    static constexpr int Mono = 1;
    static constexpr float twoPI = 2.f * M_PI;
    static constexpr int Stereo = 2;
    static constexpr int Samplerate44100 = 44100;
    static constexpr int WaveTableSize = 16384;
    static constexpr float SampleSilence = 0.f;
    static constexpr int RingbufferSize = 256;
    static constexpr int RingbufferStart = 0;
    static constexpr int RingbufferHalf = RingbufferSize / 2;
};

using WaveTableStrategy = std::function<std::vector<float>()>;
using SampleOut = std::function<float()>;
using RingbufferPtr = float*;
using BufferPtr = std::array<float,AudIO::RingbufferSize>*;
using SampleRate_t = int;


class ISignalSource {
public:
    virtual float Out() = 0;
    virtual ~ISignalSource() = default;
};
class ISignalSink {
private:
    virtual ~ISignalSink() = default;
};

template<typename T>
concept is_signal_source = requires (T obj) {
    {obj.Out()} -> std::floating_point;
};
template<typename T, typename U>
concept is_sample_multisink = requires(T obj) {
    {obj.sources}   -> std::convertible_to<std::vector<std::unique_ptr<U>>>;
};
template<typename T, typename U>
concept is_sample_singlesink = requires(T obj) {
    {obj.source}    -> std::convertible_to<std::unique_ptr<U>>;
};
template<typename T, typename U>
concept is_plugable = (is_sample_multisink<T,U> && is_signal_source<T>) || (is_sample_singlesink<T,U> && is_signal_source<T>);


