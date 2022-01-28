/*
*   Hardware / Board specific Settings
*/
#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

#include <Arduino.h>
#include <Servo.h>

// Declaration of Servo OUTPUT objects
extern Servo ServOut0;
extern Servo ServOut1;
extern Servo ServOut2;

// refresh time for Servo OUTPUT ins ms
#define SRVOUT_REFRESH 40

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

// Switching Outputs (for LEDs etc.)
#define SW0 14
#define SW1 15
#define SW2 16
#define SW3 17
#define SW4 18
#define SW5 19
#endif //NANO_BOARD

// Hardware setup function
extern void hw_setup();

#endif //HARDWARE_CONFIG_H