# RC-MultiSwitcher
PlatformIO based project to handle several RC (PWM) Servo In- and outputs as well as switched Outputs for LEDs and other loads.

## Purpose
My intention for this project was to be able to use a single RC channel for multiple purposes, like switching headlights, flashing lights, sirene etc on my RC model. To be more flexible, 2 RC channels can be decoded (simultaneously), whilst 3 PWM output channels have been added along with some digital outputs.

## Requirements
Whilst the program (POC) has been tested and runs on an Nano 3.0 clone, you may want to use something stronger like a [Teensy 3.1+ board](https://www.pjrc.com/teensy/teensy31.html) for this. The Nano causes some jitter on the servo outputs, i assume due to the interrupts used to measure the PWM signal of the 2 servo input channels interfering with the servo library code.  
If you choose a different microcontroller, my recommendation is to make sure that it is 5V tolerant on the digital inputs (just to be sure). Also remenber that you'll require inputs that support interrupts for decoding the receivers PWM signals.  
**Note:** When running on a Teensy 3.x, you can also use a serial bus interface (like iBus for FlySky) on Servo Input 0 to connect your receiver, as this will connect to the HW serial RX3 pin. However, this is not (yet) implemented into the code.

## Status
Some documentation available in comments which should help you get things up and running.  
**Update 2022-02-08:** Implemented support for Teensy 3.1/3.2 boards, Servo output signal jitter is history now!  
**Updated 2022-03-03:** Code is pretty finished now with v1.1.0. It compiles, but is not yet tested as my PCBs have not yet arrived.  
**Updated 2022-03-04:** PCB arrived, code tested and some bugs fixed. Code works now as expected.  
**Updated 2022-03-09:** Added testing mode for MOSFET outputs which can be enabled in `platformio.ini` (see `main.cpp`for details)

## Changelog

### v1.1.2
- Added SW-output testing mode
- Fixed copy/paste error

### v1.1.1
- Fixed some copy/paste errors
- Adopted in/out-processing for new sirene (does not require Servo output)
- Changed `analogWrite` handling of Switched outputs; PWMServo library sets PWM to 12bit resolution (system wide)
- optionally set PWM frequency for SW0 and SW1 (FTM1 timer) in `hardware-config.h`

### v1.1.0
- Implemented functions for processing outputs according to servo input positions (`in-out_processing.*`)
- Implemented switching MOSFET (PWM) outputs
- Added aliases (#defines) for In- and Outputs to make code easier to read (`hardware-config.h`)

### v1.0.2
- declared additional Servo in- and output pins to match hardware
- removed "low power" switched outputs -> only using MOSFET driven outputs

### v1.0.1
- Added Support for Teensy 3.1/3.2
- Added decoding function from Pulse-width to degrees (as an alternative to +/- 100%)
- Added Jitter-filter for servo inputs

  
have fun,  
Juergen