#pragma once
#include <__concepts/convertible_to.h>
#include <cmath>
#include <cstdint>
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

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

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
class IInstrument {
public:
    virtual float Out() = 0;
    SampleOut_fn out_fn = 0;
    virtual void send_midi(int, int) = 0;
    virtual ~IInstrument() = default;
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

template <typename T>
concept time_interval = requires (T obj) {
    {obj.start_time} -> std::convertible_to<u32>;
    {obj.end_time}   -> std::convertible_to<u32>;
};
template <typename T>
concept time_point = requires (T obj) {
    {obj.start_time} -> std::convertible_to<u32>;
};

enum Intersect {
    none,
    cuts_end, // new event cuts end of existing event
    contained_inside, // new event is inside existing event
    contained_outside, // old event is at least fully covered by new event
    cuts_start, // new event cuts beginning of existing event
};

template <time_point T>
int find_start_event(u32 time, const std::vector<T>& events){
   int left = 0;
   int right = events.size();
   if (time > events[right - 1].start_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if (events[mid].start_time == time) return mid;
      if (time < events[mid].start_time) {
         right = mid - 1; 
      } else if (time > events[mid].start_time) {
         left = mid + 1; 
      }
   }
   return -1;
}

// binary search on AudioEvent interval from some Timestamp_t
// find event in whiches duration interval the Timestamp_t lies
template <time_interval T>
int find_active_event (u32 time, const std::vector<T>& events) {
   int left = 0;
   int right = events.size();
   if (time > events[right - 1].end_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if (events[mid].start_time <= time && time <= events[mid].end_time) return mid;
      if (time < events[mid].start_time) {
         right = mid - 1; 
      } else if (time > events[mid].end_time) {
         left = mid + 1; 
      }
   }
   return -1;
}

inline Intersect is_intersect (u32 old_start, u32 old_end, u32 new_start, u32 new_end) {
        if (old_start >= new_start && old_end <= new_end) {
            return contained_outside;
        }
        if (old_start < new_start && old_end < new_end && old_end > new_start) {
            return cuts_end;
        }
        if (old_start > new_start && old_end > new_end &&  old_start < new_end) {
            return cuts_start;
        }
        if (old_start < new_start && old_end > new_end) {
            return contained_inside;
        }
    return none;
}
