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
        
    
        int read_index; // gets pushed into Pa Callback Output Buffer | or next buffer
        int write_index;//gets written to from source(osci, sampler etc)

    private:
        
        size_t _cap = AudIO::RingbufferSize;
        float buf[AudIO::RingbufferSize];
};
