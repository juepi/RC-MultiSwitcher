/*
 * Servo decoder Functions
 */

#include <Arduino.h>
#include "hardware-config.h"
#include "servo_decoder.h"

// Variable definitions
volatile unsigned short SIN0_uS = 0;         // length of PWM signal in µS
volatile unsigned long SIN0_LAST_UPDATE = 0; // millis() of last servo PWM decode
volatile unsigned long SIN0_RE_micros = 0;   // micros() of rising edge (for length measurement in ISR)
volatile unsigned short SIN1_uS = 0;
volatile unsigned long SIN1_LAST_UPDATE = 0;
volatile unsigned long SIN1_RE_micros = 0;

volatile boolean b_SIN0_newPos = false; // new position detected?
volatile boolean b_SIN1_newPos = false;

void ISR_SIN0()
{
    // Rising edge
    if (digitalRead(SIN0) == HIGH)
    {
        // save the current micros
        SIN0_RE_micros = micros();
    }
    else
    {
        // Falling edge, calculate PWM length
        if (SIN0_RE_micros && (b_SIN0_newPos == false))
        {
            SIN0_uS = (unsigned short)(micros() - SIN0_RE_micros);
            SIN0_RE_micros = 0;
            // Signal new position available
            b_SIN0_newPos = true;
            SIN0_LAST_UPDATE = millis();
        }
    }
}

void ISR_SIN1()
{
    // Rising edge
    if (digitalRead(SIN1) == HIGH)
    {
        // save the current micros
        SIN1_RE_micros = micros();
    }
    else
    {
        // Falling edge, calculate PWM length
        if (SIN1_RE_micros && (b_SIN1_newPos == false))
        {
            SIN1_uS = (unsigned short)(micros() - SIN1_RE_micros);
            SIN1_RE_micros = 0;
            // Signal new position available
            b_SIN1_newPos = true;
            SIN1_LAST_UPDATE = millis();
        }
    }
}

short Servo_PWM_to_Pct(unsigned int PWMlength, short OldPctVal, byte DeadZone)
{
    short Percent_Pos = 0;
    unsigned short Neutral = SRV_CENTER; //just to avoid compiler warning
    if (PWMlength >= (Neutral + DeadZone))
    {
        Percent_Pos = map(PWMlength, SRV_CENTER, SRV_MAX, 0, 100); // 0% - 100%
    }
    else if (PWMlength <= (Neutral - DeadZone))
    {
        Percent_Pos = map(PWMlength, SRV_MIN, SRV_CENTER, -100, 0); // -100% - 0%
    }
    else
    {
        Percent_Pos = 0; //Servo Neutral within dead zone
    }
    if (abs(Percent_Pos - OldPctVal) >= JITTER)
    {
        return Percent_Pos;
    }
    // Jitter detected, return old value
    return OldPctVal;
}

short Servo_PWM_to_Deg(unsigned int PWMlength, short OldDegVal)
{
    short Deg_Pos = 0;
    unsigned short Neutral = SRV_CENTER; //just to avoid compiler warning
    if (PWMlength > Neutral)
    {
        Deg_Pos = map(PWMlength, SRV_CENTER, SRV_MAX, 91, 180); // 91 - 180°
    }
    else if (PWMlength < Neutral)
    {
        Deg_Pos = map(PWMlength, SRV_MIN, SRV_CENTER, 0, 89); // 0 - 89°
    }
    else
    {
        Deg_Pos = 90; //Servo Neutral 90°
    }
    if (abs(Deg_Pos - OldDegVal) >= JITTER)
    {
        return Deg_Pos;
    }
    // Jitter detected, return old value
    return OldDegVal;
}