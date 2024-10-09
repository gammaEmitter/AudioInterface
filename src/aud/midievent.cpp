#include "midievent.h"
bool MidiEventCompare (const MidiEvent& lhs, const MidiEvent& rhs) {
        return lhs.start_time < rhs.start_time;
};
