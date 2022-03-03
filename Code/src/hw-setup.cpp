/*
 * Common Functions
 */
#include <Arduino.h>
#include "hardware-config.h"
#include "generic-config.h"
#include "servo_decoder.h"
#ifdef NANO_BOARD // board-specific Servo library selection
#include <Servo.h>
#else
#include <PWMServo.h>
#endif // Servo library selection

// Create Servo objects for OUTPUT Servos (board specific)
#ifdef NANO_BOARD
Servo ServOut0;
Servo ServOut1;
//Servo ServOut2;
#else
PWMServo ServOut0;
PWMServo ServOut1;
//PWMServo ServOut2;
#endif

// Initialize Switched Output Array
short Switches[6][2] = {{SW0,0},{SW1,0},{SW2,0},{SW3,0},{SW4,0},{SW5,0}};

// Initialize Servo Arrays
// OUTPUTS centered by default
short SOUT_POS[2] = {90,90};

// INPUTS set to invalid by default
short SIN_POS[2][2] = {{0,0},{0,0}};


// Hardware Setup function (called in setup loop)
void hw_setup()
{
    // configure digital Outputs (Switches)
#ifdef ONBOARD_LED
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LEDOFF);
#endif
    pinMode(SW0, OUTPUT);
    digitalWrite(SW0, LOW);
    pinMode(SW1, OUTPUT);
    digitalWrite(SW1, LOW);
    pinMode(SW2, OUTPUT);
    digitalWrite(SW2, LOW);
    pinMode(SW3, OUTPUT);
    digitalWrite(SW3, LOW);
    pinMode(SW4, OUTPUT);
    digitalWrite(SW4, LOW);
    pinMode(SW5, OUTPUT);
    digitalWrite(SW5, LOW);

#ifdef PWM_HZ
    analogWriteFrequency(SW0, PWM_HZ);
    analogWriteFrequency(SW1, PWM_HZ);
    analogWriteFrequency(SW2, PWM_HZ);
    analogWriteFrequency(SW3, PWM_HZ);
    analogWriteFrequency(SW4, PWM_HZ);
    analogWriteFrequency(SW5, PWM_HZ);
#endif
    
    // Attach OUTPUT Servos
    ServOut0.attach(SOUT0);
    ServOut1.attach(SOUT1);
    //ServOut2.attach(SOUT2);

    //Setup interrupts for servo Inputs
    attachInterrupt(digitalPinToInterrupt(SIN0), ISR_SIN0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SIN1), ISR_SIN1, CHANGE);

    // start serial port and digital Outputs
#ifdef SERIAL_OUT
    Serial.begin(BAUD_RATE);
#endif
}
