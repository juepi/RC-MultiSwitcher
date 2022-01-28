/*
 * RC-MultiSwitcher
 */

#include <Arduino.h>
#include "hardware-config.h"
#include "generic-config.h"
#include "common-functions.h"
#include "servo_decoder.h"
#include <Servo.h>

// Variables to store Servo Positions and stati
// 0 to 180° for OUTPUTS
short SOUT0pos = 0;
short SOUT1pos = 0;
short SOUT2pos = 0;
// -120% to +120% for INPUTS
short SIN0pos = 0;
short SIN1pos = 0;
// will be set to TRUE if servo positions decoded within SRV_TIMEOUT
boolean SIN0_OK = false;
boolean SIN1_OK = false;

// Helper Vars
unsigned long SIN0_Prev_Frame = 0;
unsigned int SIN0_FrameLen = 0;
unsigned long SIN1_Prev_Frame = 0;
unsigned int SIN1_FrameLen = 0;
unsigned long SrvOut_last_refresh = 0;

/*
 * Setup
 * ========================================================================
 */
void setup()
{
  hw_setup();
  DEBUG_PRINTLN();
  DEBUG_PRINTLN(FIRMWARE_NAME);
  DEBUG_PRINTLN(FIRMWARE_VERSION);
#ifdef ONBOARD_LED
  // Signal setup finished
  ToggleLed(LED, 200, 6);
#endif
  DEBUG_PRINTLN("Setup finished.");
}

/*
 * Main Loop
 * ========================================================================
 */
void loop()
{
  // Handle new signals from INPUT Servos
  if (b_SIN0_newPos)
  {
    SIN0pos = Servo_PWM_to_Pct(SIN0_uS, DEFAULT_DEAD_ZONE);
    b_SIN0_newPos = false;
  }
  if (b_SIN1_newPos)
  {
    SIN1pos = Servo_PWM_to_Pct(SIN1_uS, DEFAULT_DEAD_ZONE);
    b_SIN1_newPos = false;
  }

  // Verify validity of servo INPUT signals (signals received within SRV_TIMEOUT)
  if (millis() <= (SIN0_LAST_UPDATE + SRV_TIMEOUT))
  {
    SIN0_OK = true;
  }
  else
  {
    SIN0_OK = false;
  }
  if (millis() <= (SIN1_LAST_UPDATE + SRV_TIMEOUT))
  {
    SIN1_OK = true;
  }
  else
  {
    SIN1_OK = false;
  }

  // Copy IN0 to OUT0 for testing
  SOUT0pos = (short)map(SIN0pos, -100, 100, 0, 180); // map from +/-100% to 0..180° for Servo library

  // Write to OUTPUT Servos only once within SRVOUT_REFRESH
  if (millis() - SrvOut_last_refresh >= SRVOUT_REFRESH)
  {
    // do not write to OUTPUT servos too fast
    SrvOut_last_refresh += SRVOUT_REFRESH;
    ServOut0.write(SOUT0pos);

    // Servo INPUT Debug output (added here to avoid too much load on the serial port):
    DEBUG_PRINTLN("SIN0:\t" + String(SIN0pos) + "\t\t SIN1:\t" + String(SIN1pos) + "\t\t SOUT0:\t" + String(SOUT0pos));
  }

#ifdef ONBOARD_LED
  // Signal setup finished
  ToggleLed(LED, 1, 1);
#endif
}