# RC-MultiSwitcher
PlatformIO based project to handle several RC (PWM) Servo In- and outputs as well as switched Outputs for LEDs and other loads.

## Purpose
My intention for this project was to be able to use a single RC channel for multiple purposes, like turning on headlights, flashing lights, siren etc on my RC model. To be more flexible, 2 RC channels can be decoded (simultaneously), whilst 3 PWM (servo library) output channels have been added along with some digital outputs.

## Requirements
Whilst the program has been tested and runs on an Nano 3.0 clone, you may want to use something stronger like a [Teensy 3.1+ board](https://www.pjrc.com/teensy/teensy31.html) for this. The Nano causes some jitter on the servo outputs, i assume due to the interrupts used to measure the PWM signal of the 2 servo input channels interfering with the servo library code.  
If you choose a different microcontroller, my recommendation is to make sure that it is 5V tolerant on the digital inputs (just to be sure). Also remenber that you'll require inputs that support interrupts for decoding the receivers PWM signals.

## Status
This is work in progress, the current code is a POC on decoding the 2 RC channels along with servo output. Still much work to do adding the functionality i want and also a PCB to hook things up to.  
Some documentation available in comments which should help you get things up and running.  
**Update 2022-02-08:** Implemented support for Teensy 3.1/3.2 boards, Servo output jitter is history now!

## Changelog
### v1.0.1
- Added Support for Teensy 3.1/3.2
- Added decoding function from Pulse-width to degrees (as an alternative to +/- 100%)
- Added Jitter-filter for servo inputs

  
have fun,  
Juergen