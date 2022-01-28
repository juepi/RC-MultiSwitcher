/*
 * Common Functions
 */
#include <Arduino.h>
#include "hardware-config.h"
#include "generic-config.h"
#include "servo_decoder.h"
#include <Servo.h>

// Create Servo objects for OUTPUT Servos
Servo ServOut0;
Servo ServOut1;
Servo ServOut2;

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

    // Attach OUTPUT Servos
    ServOut0.attach(SOUT0);
    ServOut1.attach(SOUT1);
    ServOut2.attach(SOUT2);

    //Setup interrupts for servo Inputs
    attachInterrupt(digitalPinToInterrupt(SIN0), ISR_SIN0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SIN1), ISR_SIN1, CHANGE);

    // start serial port and digital Outputs
#ifdef SERIAL_OUT
    Serial.begin(BAUD_RATE);
#endif
}
