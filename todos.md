# TODO

`Rewrite section`

- [ ] have 1 AudioEventMap, not one for every channel.
- [ ] still tree like recursion from function pointer to function pointer, but: ...
  > Out function for every type of data source (oscillator, audioeventmap, adsr, fade...)
  > together with index of the source in the array that holds its data

- [ ] 

## AudioInterface

### `xChannel`

> channel source vector of SampleOut_fn --> channel has no access to `has_set_source` conforming object
>
> - [ ] adding source to vector shall invoke connect (in of new element, out of previous element): free function also handling inserting in the middle
> - [ ] adding a "effects" processing chain from AudioEvent --> final output of Out()
> - [ ]  
> - [ ]  

### `AudioEvent`

>
> - [x] add `Fade_in` and `Fade_out` to AudioEvent
> - [x] add offset_front to AudioEvent
> - [x] add Out() function to AudioEvent 
>

### `Event-Queues`

>
> - [x] adjust event on collision with new (added) event: adjust event `duration`
>
> - [x] Looping ((1) simplest implementation for audioeventmap)
> - [x] Loops: behavior of events surpassing loop `end` position
> - [ ]
> - [ ]
>

### `Midi`
> - [x] total revision of signal pathing, just think of how midi clips might get implemented. I cannot just call 
        ring_buffer->pull() on empty because it might change the phase of the underlying source
> - [ ] per Midi-Input (keyboard) MidiController class that can have one (or multiple?) active midi-targets, 
        which get NOTE events sent -> publisher subscriber, how performant is it


### `Audio File Formats`
>
> - [ ] mp3
> - [ ] ogg - work in progress
> - [x] flac
>

### `New Component`

> - [ ] Synth instrument
> - [ ] Sampler Instrument
>

- [ ] __Curve-Tool__ Python Tool to ADSR and LFO curve tool
  - [ ] code generation
