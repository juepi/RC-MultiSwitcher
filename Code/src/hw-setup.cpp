/*
 * Hardware Setup Functions
 */
#include <Arduino.h>
#include "hardware-config.h"
#include "generic-config.h"
#include "servo_decoder.h"
#ifdef NANO_BOARD // board-specific Servo library selection
#include <Servo.h>
#else
#include <PWMServo.h>
#ifdef IBUS
#include "iBUS.h"
#endif
#endif // Servo library selection

// Create Servo objects for OUTPUT Servos (board specific)
#ifdef NANO_BOARD
Servo ServOut0;
//Servo ServOut1;
#else
PWMServo ServOut0;
//PWMServo ServOut1;
#endif

// Initialize Switched Output Array
int Switches[6][2] = {{SW0,0},{SW1,0},{SW2,0},{SW3,0},{SW4,0},{SW5,0}};

// Initialize Servo Arrays
// OUTPUTS centered/neutral by default
short SOUT_POS[1] = {90};

// INPUTS set to invalid by default
short SIN_POS[6][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

// Hardware Setup function (called in setup loop)
void hw_setup()
{
    // configure digital Outputs (Switches)
#ifdef ONBOARD_LED
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
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

#ifdef SW_TESTING
    // for manually testing SW* outputs
    pinMode(SIN3,INPUT);
    //SOUT3 set HIGH, can be used as 3V3 source for SIN3
    pinMode(SOUT3,OUTPUT);
    digitalWrite(SOUT3, HIGH);
#endif

#ifdef FTM1_FREQ
    analogWriteFrequency(FTM1_PIN, FTM1_FREQ);
#endif

    // Attach OUTPUT Servos
    ServOut0.attach(SOUT0);
    //ServOut1.attach(SOUT1);

    //Setup interrupts for servo Inputs
#ifndef IBUS
    attachInterrupt(digitalPinToInterrupt(SIN0), ISR_SIN0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SIN1), ISR_SIN1, CHANGE);
#else
    IBUS_SERIAL.begin(IBUS_BPS);
    while(!IBUS_SERIAL)
    {
        delay(10);
    }
#endif

    // start serial port for debugging
#ifdef SERIAL_OUT
    Serial.begin(BAUD_RATE);
#endif
}
