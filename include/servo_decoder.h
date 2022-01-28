/*
*   Function declarations for RC servo decoding
*/
#ifndef SRVDEC_H
#define SRVDEC_H

#include <Arduino.h>
#include "generic-config.h"

// Servo Pulse widths in µS
#define SRV_CENTER 1500
#define SRV_MIN 900     // added 20% spare to the default 500µs
#define SRV_MAX 2100
#define DEFAULT_DEAD_ZONE 30 // Servo dead zone for neutral in µs (+/-);

// Declare servo input as dead if no PWM decode has happend after 100ms
#define SRV_TIMEOUT 100

// Interrupt Service routines
extern void ISR_SIN0();
extern void ISR_SIN1();

// Servo Calculation functions
extern short Servo_PWM_to_Pct(unsigned int PWMlength, byte DeadZone);

// Variable declarations
extern volatile unsigned short SIN0_uS;                    // length of PWM signal in µS
extern volatile unsigned long SIN0_LAST_UPDATE; // millis() of last servo PWM decode
extern volatile unsigned long SIN0_RE_micros;   // micros() of rising edge (for PWM length measurement in ISR)
extern volatile unsigned short SIN1_uS;
extern volatile unsigned long SIN1_LAST_UPDATE;
extern volatile unsigned long SIN1_RE_micros;

extern volatile boolean b_SIN0_newPos; // new PWM signal decoded?
extern volatile boolean b_SIN1_newPos;

#endif //SRVDEC_H