//
//

#include "ringbuffer.h"
#include "iodef.h"

inline float _ringbuffer_dummy () {return 0.f;}

Ringbuffer::Ringbuffer() { 
    for (int i = 0; i < _cap; ++i){
        buf[i] = float();
    }
    source = &_ringbuffer_dummy;
    
    read_index = 0;
    write_index = _cap - 1;
};

size_t Ringbuffer::capacity() const {
    return _cap;

}

void Ringbuffer::increment() {
    read_index++;
    write_index++;
    read_index = read_index % _cap;
    write_index = write_index  % _cap;
}

float Ringbuffer::pull(){
    float tmp = buf[read_index];
    buf[write_index] = source();
    increment();
    return tmp;  
}


void Ringbuffer::set_source(SampleOut_fn func) {
    source = func;
} 

