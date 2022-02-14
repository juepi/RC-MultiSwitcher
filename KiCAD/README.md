# RC-MultiSwitcher
Hardware part of the project. Designed using KiCAD6, SMT parts used from the [JLCPCB parts list](https://jlcpcb.com/parts) to allow pre-assembling all the SMT parts.

## Purpose
Provide power to teensy MCU from BEC (up to 7.2V, Servo input 1) using LDO regulator provide hardware connections for Servo in- and outputs as wells as 6 N-channel MOSFET switched outputs (all 6 support PWM). The PCB has a 5A polyfuse installed at the power input to avoid overload (however, you will still have to make sure that you do not overload your BEC).

## Requirements
The [KiCAD Teensy libraries](https://github.com/XenGi/teensy_library) have been used for this board, they are included in the lib folder. The footprint has been slightly adopted to include only the main 2 pin-rows of the Teensy.

## Status
Schematic and layout finished, manufacturing data for [jlcpcb.com](https://jlcpcb.com/) added in "production" subfolder. 

## Changelog
###v1.0
- Minor layout improvements
- changed C1 to different part with lower MOQ
- published manufacturing data
  
    
have fun,  
Juergen