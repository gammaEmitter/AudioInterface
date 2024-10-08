#pragma once
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <vector>
#include <functional>
#include <concepts>
#include <array>
#include <queue>
#include <memory>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using WaveTableStrategy_fn = std::function<std::vector<float>()>;
using SampleOut_fn = std::function<float()>;
using SetFrequency_fn = std::function<void(float)>;
using RingbufferPtr = float*;
using SampleRate_t = int;

namespace AudIO {

    static constexpr int Mono = 1;
    static constexpr float twoPI = 2.f * M_PI;
    static constexpr int Stereo = 2;
    static constexpr SampleRate_t Samplerate44100 = 44100;
    static constexpr int WaveTableSize = 16384;
    static constexpr float SampleSilence = 0.f;
    static constexpr int RingbufferSize = 256;
    static constexpr int RingbufferStart = 0;
    static constexpr int RingbufferHalf = RingbufferSize / 2;
};
class IChannel {
public:
    virtual float Out() = 0;
    virtual IChannel& add_source(SampleOut_fn) = 0;
    virtual ~IChannel() = default;
};
enum ChannelType {
    Audio,
    Midi,
};
class IFreqAdjustable {
public:
    virtual void setFreq(float) = 0;
    virtual ~IFreqAdjustable() = default;
};

class ISignalSource {
public:
    virtual float Out() = 0;
    virtual ~ISignalSource() = default;
};
class ISignalSink {
private:
    virtual ~ISignalSink() = default;
};

template <typename T>
concept has_freq_set = requires (T obj, float freq) {
    {obj.set_freq(freq)}; 
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


