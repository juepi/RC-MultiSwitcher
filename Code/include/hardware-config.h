/*
*   Hardware / Board specific Settings
*/
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include <Arduino.h>
#ifdef NANO_BOARD // board-specific Servo library selection
#include <Servo.h>
#else
#include <PWMServo.h>
#endif // Servo library selection

// Declaration of Servo OUTPUT objects (board specific)
#ifdef NANO_BOARD
extern Servo ServOut0;
extern Servo ServOut1;
extern Servo ServOut2;
#else
extern PWMServo ServOut0;
extern PWMServo ServOut1;
extern PWMServo ServOut2;
#endif

// refresh time for Servo OUTPUTS ins ms
#define SRVOUT_REFRESH 40

// Define PINS to use for each in- and output
#ifdef NANO_BOARD
#define LED 13
// LED is active low
#define LEDON LOW
#define LEDOFF HIGH

// Servo INPUTS
#define SIN0 2
#define SIN1 3

// Servo OUTPUTS
#define SOUT0 9
#define SOUT1 10
#define SOUT2 11

// Switched Outputs (for LEDs etc.)
#define SW0 14
#define SW1 15
#define SW2 16
#define SW3 17
#define SW4 18
#define SW5 19
#endif //NANO_BOARD

#ifdef T31_BOARD
#define LED 13
// LED is active low
#define LEDON LOW
#define LEDOFF HIGH

// Servo INPUTS
#define SIN0 7
#define SIN1 8
// Additional Servo inputs, currently unsused but prepared in hardware
#define SIN2 11
#define SIN3 12

// Servo OUTPUTS
#define SOUT0 20
#define SOUT1 21
// Additional Servo outputs, currently unused but prepared in hardware
#define SOUT2 22
#define SOUT3 23

// Switched Outputs (N-channel MOSFETs sum current 5A -> polyfuse -> watch out for your BEC!)
// All of these pins support PWM!
#define SW0 3
#define SW1 4
#define SW2 5
#define SW3 6
#define SW4 9
#define SW5 10
#endif //T31_BOARD

// Hardware setup function
extern void hw_setup();

#endif //HARDWARE_CONFIG_H