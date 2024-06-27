#include "audioeventqueue.h"


void AudioEventQueue::add_event (const AudioEvent&& evt) {
    queue.push(std::move(evt)); 
    if (queue.size() == 1) {
        next_event = queue.top();
    } 
}
