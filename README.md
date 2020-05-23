# Particle_Flocking_MIDI

This is an audio application I wrote using openframeworks that converts positional data of particles on screen flocking towards a mouse cursor to output MIDI CC values. The MIDI output is mapped directly to a Korg Prologue Synth.


![](https://github.com/nightshining/Particle_Flocking_MIDI/blob/master/bin/data/image/flocking_ex.gif?raw=true)

### How to Run: 

in the **/bin** folder I've included the software build. It is for Mac OS. To compile the code you will need to download [openFrameworks](https://openframeworks.cc/download/). You will also need to download and install the [ofxMidi](https://github.com/danomatika/ofxMidi) addon which is a dependency for this code to run. 

The MIDI CC values can be sent directly out of a [Virtual Midi Bus](https://help.ableton.com/hc/en-us/articles/209774225-How-to-setup-a-virtual-MIDI-bus) or the audio card MIDI channel. In my case I utilized a [UM-ONE](https://www.roland.com/us/products/um-one/) and connected it directly to my synthesizer. 
