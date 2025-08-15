#pragma once

#include "adsr.h"
#include "allocator.h"
#include "clockbase.h"
#include "iodef.h"
#include "midievent.h"
#include <exception>
#include <optional>

struct MidiEventMap {
    SignalPath                      path            {};
    SignalPath*                     generator_path  {};
    OscFreq*                        recv_freq       {};
    ADSR*                           recv_note       {};
    MidiEvent*                      events[64]      {};
    u8                              size_events     {};
    float                           carry_stereo    {};
    float                           gain            {};
    bool                            left_pos        {};
    bool                            stereo_gen      {};
};
void init_midi_event_map(AAllocator& alloc, MidiEventMap*& map,  OscFreq* recv_freq, ADSR* recv_note);
void add_event_midi_event_map(MidiEventMap* map, MidiEvent* evt);
void generator_set_midi_event_map (MidiEventMap*& map, SignalPath* generator_path, bool stereo);

inline void out_midi_eventmap(void* arg) {

    MidiEventMap* map = (MidiEventMap*) arg;
    float out = AudIO::SampleSilence;
    if (map->size_events == 0) {
        *(map->path.out) = out;
        return;
    }

    /*
     *  TODO: rewrite to incremental event finding. the events array is already sorted
     */
    Timestamp_t curr_time = Clockbase::current_time.load();
    auto idx = find_start_event(curr_time, map->events, map->size_events);
    if (idx != -1) {
        // printf("(%u) found event with start time: %d, index %d, note type %d\n",curr_time, map->events[idx]->start_time, idx, map->events[idx]->ntype );
        if (NoteType::ON == map->events[idx]->ntype) {
            set_freq(map->recv_freq, note_to_hz(map->events[idx]->note, 440.f));
            map->recv_note->state.store(ADSR::State::Attack);
        } else if (NoteType::OFF == map->events[idx]->ntype) {
            ADSR::State state = map->recv_note->state.load();
            if (state == ADSR::State::Off || state == ADSR::State::Release) return;
            fade_into_adsr(map->recv_note, ADSR::State::Release);
        }
    }
    if (map->stereo_gen) {
        *(map->path.out) = *(map->generator_path->out);
    } else {
        if (map->left_pos) {
            *(map->path.out) =  *(map->generator_path->out);
            map->carry_stereo = *(map->path.out);  
        } else {
            *(map->path.out) = map->carry_stereo;
        }
        map->left_pos = !map->left_pos;
    }
    return;
}
