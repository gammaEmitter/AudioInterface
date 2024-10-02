# TODO

## AudioInterface

### `xChannel`

> channel source vector of SampleOut_fn --> channel has no access to `has_set_source` conforming object
>
> - [ ] adding source to vector shall invoke connect (in of new element, out of previous element): free function also handling inserting in the middle
> - [ ]  

### `Event-Queues`

>
> - [ ] adjust event on collision with new (added) event: adjust event `duration`
>
> - [x] Looping ((1) simplest implementation for audioeventmap)
> - [ ] Loops: behavior of events surpassing loop `end` position
> - [ ]
> - [ ]
>

### `Midi`
> - [ ] total revision of signal pathing, just think of how midi clips might get implemented. I cannot just call 
        ring_buffer->pull() on empty because it might change the phase of the underlying source
> - [ ] per Midi-Input (keyboard) MidiController class that can have one (or multiple?) active midi-targets, 
        which get NOTE events sent -> publisher subscriber, how performant is it


### `Midi-Messaging`
> - [ ] `Note OFF` event triggers fade from different Note active.
   should instead only trigger fade, if `note_num` corresponds to active note
> - [ ] classes `MidiReceiver` and `MidiListener` have different initialisation methods upon needing to be default-constructable, should have consistent way
>

### `Audio File Formats`
>
> - [ ] mp3
> - [ ] ogg
> - [ ] flac
>

### `New Component`

> - [ ] Synth instrument
> - [ ] Sampler Instrument
>

- [ ] __Curve-Tool__ Python Tool to ADSR and LFO curve tool
  - [ ] code generation
