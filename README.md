# AudioInterface

The goal is to build an audio application that provides different sources 
and can mix them into an output stream.



This is a learning and training project and does have bugs and unhandled cases.

## Build

```bash
mkdir build
cd build
cmake -DPA_BUILD_SHARED_LIBS=ON .. # wip workaround: use shared lib
              # of PortAudio if alsa is not properly linked staticly
make
```
Not tested on Windows
