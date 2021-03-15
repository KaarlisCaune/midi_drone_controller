# Arduino MIDI musical drone controller

This is a simple latching MIDI controller. Its "keys" are toggle switches, thus it's meant to play continuos notes or chords.

Also features:
* LEDs for each toggle switch to indicate on / off position
* Switchable low, middle and high octaves

Implementation is extremely simple. Arduino just reads the state of the switches, compares it to its own internal state state and sends out noteOn and noteOff MIDI messages. There are some more checks for lower / higher octaves, but that's about it.

[MIDI drone controller](controller.png)

## Wiring

Wiring is simple too, if you use an Arduino Mega - in this case not because of the digital read pin count, but because of max amperage.

The LEDs are not controlled by the Arduino, rather they are directly wired to the toggle switches ground and 5V. 

Since there are 15 LEDs, each possibly pulling about 20mA, this project has the potential of damaging smaller boards - don't attempt that without a safe solution, like using transistors. Mega has multiple 5V / grounds, so when each 5V is connected to max. 5 LEDs, it's pretty safe. Unless you enjoy pink noise, most LED's won't be turned on all the time though.

Part list:

* Arduino Mega
* 15x 2-way toggle switch (three pins, middle ground, ON-ON)
* 15x LEDs
* 17x 220 ohm resistors
* 1x MIDI DIN female connector
* Wires
* Something for your enclosure - I used plexiglass and wood

Wiring for two switches and the MIDI connection:

[wiring](wiring.png)

## Possible future improvements

It should be relatively easy to add a potentiometer for tempo and turn this into an arpeggiator.