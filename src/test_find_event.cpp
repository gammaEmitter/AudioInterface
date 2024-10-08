#include "../inc/aud/audioevent.h"
#include "../inc/aud/audioeventqueue.h"
#include "../inc/aud/clockbase.h"
#include <vector>
#include "resourcemanager.h"
#include <cassert>

// int find_active_event (Timestamp_t time, const std::vector<AudioEvent>& events) {
//    int left = 0;
//    int right = events.size();
//    printf("Target Time Query: %d\n", time);
//    printf("Event Right end_time: %d\n\n\n", events[right- 1].end_time);
//    if (time > events[right - 1].end_time) return right;
//    while (left <= right) {
//       int mid = (left+right) / 2;
//
//       printf("Mid Index: %d\n", mid);
//       printf("Current Query start_time : %d\n", events[mid].start_time);
//       printf("Current Query end_time : %d\n", events[mid].end_time);
//       if (events[mid].start_time <= time && events[mid].end_time >= time) return mid;
//       //decide to search in lower or upper half
//       if (time < events[mid].start_time) {
//          right = mid - 1; // truncate search bounds to lower half
//       } else if (time > events[mid].end_time) {
//          left = mid + 1; //truncate search bounds to upper half
//       }
//    }
//    return left;
// }

ResourceManager &resources{ResourceManager::getInstance()};

int main (int argc, char *argv[]) {
   // std::vector<AudioEvent> events {};
   // auto tock = resources.addWAV("../res/tock.wav").get();
   // auto kick = resources.addWAV("../res/kick.wav").get();
   // events.push_back({kick, timeFromBeats(1, 0)});
   // events.push_back({kick, timeFromBeats(2, 0)});
   // events.push_back({kick, timeFromBeats(3, 0)});
   // events.push_back({kick, timeFromBeats(4, 0)});
   //
   //
   //
   // for (auto& event : events) {
   //    printf("start_time: %d\n", event.start_time);
   //    printf("end_time: %d\n", event.end_time);
   //    printf("duration: %d\n", event.duration);
   //    printf("\n");
   // }
   // printf("%d\n", find_active_event(timeFromBeats(1, 2), events));

   assert(Intersect::cuts_start == is_intersect(0, 4, 0, 1));
   assert(Intersect::cuts_start == is_intersect(1, 4, 0, 3));

   assert(Intersect::cuts_end == is_intersect(0, 4, 3, 5));

   assert(Intersect::contained_inside == is_intersect(0, 4, 1, 3));
   assert(Intersect::contained_outside == is_intersect(0, 4, 0, 4));
   assert(Intersect::contained_outside == is_intersect(0, 4, 0, 5));
  return 0; 
}
