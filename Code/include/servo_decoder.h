/*
*   Function declarations for RC servo decoding
*/
#ifndef SRVDEC_H
#define SRVDEC_H

#include <Arduino.h>
#include "generic-config.h"

// Servo Pulse widths in µS
#define SRV_CENTER 1500
#define SRV_MIN 1000
#define SRV_MAX 2000
#define DEFAULT_DEAD_ZONE 10 // Servo dead zone for neutral in µs (+/-);

// Declare servo input as dead if no PWM decode has happend after 100ms
#define SRV_TIMEOUT 100

// Eliminate Jitter for Servo INPUTS
// Diffs for INPUTS lower than JITTER (no matter if % or °) will be ignored
//ATTN: potentially decreases decoding resolution, do not set too high.
#define JITTER 2

// Interrupt Service routines
#ifndef IBUS
extern void ISR_SIN0();
extern void ISR_SIN1();
#endif

// Servo Calculation functions
extern short Servo_PWM_to_Pct(unsigned int PWMlength, short OldPctVal, byte DeadZone);
extern short Servo_PWM_to_Deg(unsigned int PWMlength, short OldDegVal);

// Variable declarations
#ifndef IBUS
extern volatile unsigned short SIN0_uS;                    // length of PWM signal in µS
extern volatile unsigned long SIN0_LAST_UPDATE; // millis() of last servo PWM decode
extern volatile unsigned long SIN0_RE_micros;   // micros() of rising edge (for PWM length measurement in ISR)
extern volatile unsigned short SIN1_uS;
extern volatile unsigned long SIN1_LAST_UPDATE;
extern volatile unsigned long SIN1_RE_micros;

extern volatile boolean b_SIN0_newPos; // new PWM signal decoded?
extern volatile boolean b_SIN1_newPos;
#endif

#endif //SRVDEC_H