# RC-MultiSwitcher
Hard- and software project to handle several RC (PWM) Servo In- and outputs as well as switched Outputs for LEDs and other loads.

## Purpose
My intention for this project was to be able to use a single RC channel for multiple purposes, like switching headlights, flashing lights, siren etc on my RC model. To be more flexible, the board provides 4 PWM servo inputs as well as 4 outputs, which can be used simultaneously. It additionally supports 6 N-channel MOSFET outputs, supporting an optional free-wheeling diode for inductive loads on every output.

## Requirements
Whilst the program has been tested and runs on an Nano 3.0 clone, you may want to use something stronger like a [Teensy 3.1+ board](https://www.pjrc.com/teensy/teensy31.html) for this. The Nano causes some jitter on the servo outputs, i assume due to the interrupts used to measure the PWM signal of the 2 servo input channels interfering with the servo library code.  
If you choose a different microcontroller, my recommendation is to make sure that it is 5V tolerant on the digital inputs (just to be sure). Also remenber that you'll require inputs that support interrupts for decoding the receivers PWM signals.

## Status
This is work in progress, the current code is a POC on decoding the 2 RC channels along with servo output. Still much work to do adding the functionality i want and also a PCB to hook things up to.  
Some documentation available in comments which should help you get things up and running.  
**Update 2022-02-08:** Implemented support for Teensy 3.1/3.2 boards, Servo output jitter is history now!  
**Update 2022-02-11:** Added KiCAD project with schematic and layout for Teensy 3.1+ based MCU. KiCAD project is finished so far, will add gerber data as soon as i've finished the first order at JLCPCB.  
**Update 2022-02-14:** KiCAD project finished after some minor layout improvements. Added gerber, drilling, placement files as well as BoM in "production" subfolder.  
**Update 2022-02-24:** Implemented minor changes on PCB (v1.1): added possibility to provide power via 2pin JST XH plug; added solder-pad to short-circuit fuse (use with caution!); updated manufacturing files  
**Updated 2022-03-04:** Ordered PCB just arrived (v1.0) and works perfectly well! Not yet tested: high power load and PWM output on MOSFET switches.  

## Usage
![Bottom side of the PCB](https://github.com/juepi/RC-MultiSwitcher/blob/main/images/RC-MultiSwitcher_v1.0_top.jpg?raw=true)
![Servo Connector](https://github.com/juepi/RC-MultiSwitcher/blob/main/images/RC-MultiSwitcher_v1.0_bottom.jpg?raw=true)
  
  
have fun,  
Juergen