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
#define OUTPUT_REFRESH 40

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
#define SIN2 11
#define SIN3 12

// Servo OUTPUTS
// These Pins use Timer FTM0 set to 50Hz @ 12bit resolution by PWMServo library! Do not change!
#define SOUT0 20
#define SOUT1 21
#define SOUT2 22
#define SOUT3 23

// Switched Outputs (N-channel MOSFETs sum current 5A -> polyfuse -> watch out for your BEC!)
// All of these pins support PWM! Resolution is 12bit for all PWM pins (->PWMServo)
#define SW0 3 //FTM1 Timer
#define SW1 4 //FTM1 Timer
#define SW2 5 //FTM0 Timer!
#define SW3 6 // FTM0 Timer!
#define SW4 9 // FTM0 Timer!
#define SW5 10 // FTM0 Timer!

// PWM Frequency for Switched Outputs SW0 and SW1 (optional, defaults to 488Hz for Teensy 3.1)
// NOTE: Only change for FTM1! Resolution is 12bit for all PWM pins (->PWMServo)
//#define FTM1_FREQ 1000
#define FTM1_PIN SW0
#endif //T31_BOARD

// 2D Array for switched Outputs
// First Row: PIN of switch Element 0 = SW0, Element 1 =SW1 ...
// Second Row: OUTPUT-State of switch (0..100% -> PWM!)
extern short Switches[6][2];

// Create some human readable Switch Aliases
#define PUMP 0
#define HEADLIGHTS 1
#define BLUELAMP 2
#define SIRENE 3
#define SW_PIN 0
#define SW_STATE 1

// Array for desired Servo OUTPUT Positions (0..180°)
// Usage: Element 0 = SOUT0, Element 1 = SOUT1 ...
// we currently use 1 out of 4 servo outputs
extern short SOUT_POS[1];

// Create some human readable Servo Output Aliases
#define WINCH 0

// 2D Array for measured Servo INPUT Positions (0..180° or -100%..100%)
// First row: measured servo position; second row: servo signal status (0=SignalInvalid;1=Degrees;2=Percent)? -> SignalInvalid is set if input is not updated within SRV_TIMEOUT
// Usage: Element 0 = SIN0, Element 1 = SIN1 ...
// we currently use 2 out of 4 servo inputs
extern short SIN_POS[2][2];

// Create some human readable Servo Input Aliases
#define RX_CH5 0
#define RX_CH6 1
#define POS 0
#define STAT 1
#define STAT_ERR 0
#define STAT_DEG 1
#define STAT_PCT 2

// Hardware setup function
extern void hw_setup();

#endif //HARDWARE_CONFIG_H