//
#pragma once
#include <cstddef>
#include <iostream>
#include "iodef.h"

class Ringbuffer {
    public:
        Ringbuffer ();

        Ringbuffer(const Ringbuffer& ringbuffer) = delete;
        Ringbuffer& operator=(const Ringbuffer& ringbuffer) = delete;

        Ringbuffer(Ringbuffer&& ringbuffer) {
            for (int i = 0; i < _cap; ++i) {
                buf[i] = std::move(ringbuffer.buf[i]);
            } 
        }
        Ringbuffer& operator=(Ringbuffer&& ringbuffer) {
            if (this != &ringbuffer) {
                for (int i = 0; i < _cap; ++i) {
                    buf[i] = std::move(ringbuffer.buf[i]);
                } 
                _cap = ringbuffer._cap;
            }
            return *this;
        }
        

        float& operator[](int i) {
            i = i % _cap;
            return buf[i];
        }

        void insert(float& val);
        void increment();
        size_t capacity () const;
        float pull();
        void set_source(SampleOut func);
        
    
        int read_index; // gets pushed into Pa Callback Output Buffer | or next buffer
        int write_index;//gets written to from source(osci, sampler etc)

    private:
        
        SampleOut source;
        //Ringbuffer* source = nullptr; // points at ringbufer.buff[read_index] one lower in the hierachy
        size_t _cap = AudIO::RingbufferSize;
        float buf[AudIO::RingbufferSize];
};
