#include "midimessaging.h"
#include "clockbase.h"
#include "iodef.h"
#include "libremidi/input_configuration.hpp"
#include "libremidi/libremidi.hpp"
#include "midievent.h"
#include <memory>



void MidiReceiver::Init(IFreqAdjustable* osc, ADSR* env_gen) {
    instrument = osc;
    adsr = env_gen;
    for (int i = 21; i < 108; ++i) {
        std::string note_num = std::to_string(i);
        this->bind("OFF "+ note_num, [&, i, note_num](){
            auto state = adsr->state.load();
            if (state == (ADSR::State::Off)) return;
            if (state == (ADSR::State::Release)) return;
            adsr->fade_into(ADSR::Release);
        });
        this->bind("ON "+ note_num, [&, i]() {
            float freq = 440.0 * pow(2,((i - 69.0f))/12.0f);
            instrument->setFreq(freq);
            adsr->fade_into(ADSR::Attack);
        });
    }
}

MidiListener::MidiListener(Messagable& midi_receiver, int port_num) {
    libremidi::input_configuration input_conf {
        .on_message = [&](const libremidi::message& message) {
            std::string type {};
            if (message.get_message_type() == libremidi::message_type::NOTE_ON) {
                type = "ON";
            } else if (message.get_message_type() == libremidi::message_type::NOTE_OFF) {
                type = "OFF";
            }
            this->send(midi_receiver, type + " " +  std::to_string((int)message[1]), Message::Execution::Immediate);
        },
        .ignore_sysex = false,  
        .ignore_timing = false,
        .ignore_sensing = false,
    };
    midi_conn = std::make_unique<libremidi::midi_in>(input_conf);

    auto ports = libremidi::observer{{}, observer_configuration_for(midi_conn->get_current_api())}
                   .get_input_ports();
    midi_conn->open_port(ports[port_num]);
}
