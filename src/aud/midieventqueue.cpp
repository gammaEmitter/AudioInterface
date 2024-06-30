#include "midieventqueue.h"
#include "iodef.h"
#include "midievent.h"

MidiEventQueue::MidiEventQueue(Messagable& midi_receiver) {
    midi_rec = &midi_receiver;
}

void MidiEventQueue::add_event(const MidiEvent&& evt) {
    queue.push(std::move(evt));
    if (queue.size() == 1) {
        next_event = queue.top();
    }
}
