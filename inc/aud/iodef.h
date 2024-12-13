#pragma once
#include <__concepts/convertible_to.h>
#include <cmath>
#include <cassert>
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
// using SampleOut_fn = std::function<float()>;
typedef void(*SampleOut_fn)(void*);
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

struct OscFreq {
    float frequency_norm;
    float incr_phase;
};

struct SignalPath {
    float* in;
    float* out;
    SampleOut_fn proc;
};


inline void set_freq(OscFreq& osc_freq, float hz) {
    osc_freq.frequency_norm = hz/AudIO::Samplerate44100;
    osc_freq.incr_phase = osc_freq.frequency_norm * AudIO::twoPI;
}

inline void set_gain(float& attr, float gain) {
    if (gain >= 1.f) {
        attr = 1.f;
    } else if (gain <= 0){
        attr = 0.f;
    } else {
        attr = gain;
    }
}


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
int find_start_event(u32 time, const std::vector<T*>* events){
   int left = 0;
       int right = events->size();
       if (time > (*events)[right - 1]->start_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if ((*events)[mid]->start_time == time) return mid;
      if (time < (*events)[mid]->start_time) {
         right = mid - 1; 
      } else if (time > (*events)[mid]->start_time) {
         left = mid + 1; 
      }
   }
   return -1;
}

// binary search on AudioEvent interval from some Timestamp_t
// find event in whiches duration interval the Timestamp_t lies
template <time_interval T>
int find_active_event (u32 time, const std::vector<T*>& events) {
   int left = 0;
   int right = events.size();
   if (time > events[right - 1]->end_time) return -1;
   while (left <= right) {
      int mid = (left+right) / 2;
      if (events[mid]->start_time <= time && time <= events[mid]->end_time) return mid;
      if (time < events[mid]->start_time) {
         right = mid - 1; 
      } else if (time > events[mid]->end_time) {
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
