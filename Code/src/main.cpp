/*
 * RC-MultiSwitcher
 */

#include <Arduino.h>
#include "hardware-config.h"
#include "generic-config.h"
#include "common-functions.h"
#include "servo_decoder.h"
#include "in-out_processing.h"

// Helper Vars
unsigned long Out_last_refresh = 0;
#ifdef IBUS
bool iBUS_VALID = false;
#endif

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
#ifdef IBUS
  if (millis() - iBus_last_decode > IBUS_TIMEOUT_MS)
  {
    iBUS_VALID = false;
  }
  else
  {
    iBUS_VALID = true;
  }
#else
  // Handle new signals from INPUT Servos (Interrupt routines in servo_decoder.cpp)
  if (b_SIN0_newPos)
  {
    // SIN0 alias RX_CH5
    SIN_POS[RX_CH5][POS] = Servo_PWM_to_Deg(SIN0_uS, SIN_POS[RX_CH5][POS]);
    SIN_POS[RX_CH5][STAT] = 1; // We've decoded to degrees
    // Process Input / Output mapping
    Process_RX_CH5();
    b_SIN0_newPos = false;
  }
  if (b_SIN1_newPos)
  {
    // SIN1 alias RX_CH6
    SIN_POS[RX_CH6][POS] = Servo_PWM_to_Pct(SIN1_uS, SIN_POS[RX_CH6][POS], DEFAULT_DEAD_ZONE);
    SIN_POS[RX_CH6][STAT] = 2; // We've decoded to percent
    // Process Input / Output mapping
    Process_RX_CH6();
    b_SIN1_newPos = false;
  }
#endif

#ifdef IBUS
  if (iBUS_VALID)
  {
    // IBus_readChan reports current state in µs, just as our servo decoder
    SIN_POS[RX_CH5][POS] = Servo_PWM_to_Deg(iBus_readChan(IBUS_CH_5), SIN_POS[RX_CH5][POS]);
    SIN_POS[RX_CH5][STAT] = 1; // We've decoded to degrees
    // Process Input / Output mapping
    Process_RX_CH5();
    SIN_POS[RX_CH6][POS] = Servo_PWM_to_Pct(iBus_readChan(IBUS_CH_6), SIN_POS[RX_CH6][POS], DEFAULT_DEAD_ZONE);
    SIN_POS[RX_CH6][STAT] = 2; // We've decoded to percent
    // Process Input / Output mapping
    Process_RX_CH6();
#ifdef ONBOARD_LED
    digitalWrite(LED, LEDOFF);
#endif
  }
  else
  {
    SIN_POS[RX_CH5][STAT] = 0; // iBUS disconnected, channels invalid!
    SIN_POS[RX_CH6][STAT] = 0;
#ifdef ONBOARD_LED
    digitalWrite(LED, LEDON);
#endif
  }
#else
  // Verify validity of servo INPUT signals (signals received within SRV_TIMEOUT)
  if (millis() > (SIN0_LAST_UPDATE + SRV_TIMEOUT))
  {
    SIN_POS[RX_CH5][STAT] = 0; // SIN0 invalid!
  }
  if (millis() > (SIN1_LAST_UPDATE + SRV_TIMEOUT))
  {
    SIN_POS[RX_CH6][STAT] = 0; // SIN1 invalid!
  }
#endif

  // Write stati to Servo and switched Outputs only once within OUTPUT_REFRESH
  if (millis() - Out_last_refresh >= OUTPUT_REFRESH)
  {
    Out_last_refresh += OUTPUT_REFRESH;
    // Set OUTPUT Servo Position
    ServOut0.write(SOUT_POS[WINCH]);

    // Set switched output states
    // Note: These are PWM Outputs with 12bit resolution! 0% (0) = Always Off; 100% (4096) = Always On
    // Anything between will result in PWM
    // ATTN: keep in mind that SW2-SW5 share the FTM0 timer with the Servo outputs --> fixed at 50Hz
    // SW0 and SW1 (FTM1 timer) frequency might be changed in hardware-config.h
    for (int i = 0; i <= 5; i++)
    {
#ifdef SW_TESTING
      // SW_TESTING Mode (enable in platformio.ini)
      // SIN3 is configured as INPUT_PULLUP, thus all SW* outputs are ENABLED by default unless SIN3 is pulled to GND
      if (digitalRead(SIN3))
      {
        // Enable all SW Outputs if SIN3 = HIGH
        Switches[i][SW_STATE] = 100;
      }
      else
      {
        // If SIN3 is pulled low (default), map RX_CH5 status to every SW Output (PWM Testing)
        if (SIN_POS[RX_CH5][STAT] == 1)
        {
          Switches[i][SW_STATE] = map(SIN_POS[RX_CH5][POS], 0, 180, 0, 100);
        }
      }
#endif
      // Set SW output states
      // make sure FETs are full OFF (0-2%), ON (98-100%) or PWM in between
      // This might be important when feeding Switches from a channel which does not reach full end positions -> tweak as required
      switch (Switches[i][SW_STATE])
      {
      case 0 ... 2:
        Switches[i][SW_STATE] = 0;
        break;
      case 3 ... 97:
        break;
      case 98 ... 100:
        Switches[i][SW_STATE] = 100;
        break;
      }
      // write to Output
      analogWrite(Switches[i][SW_PIN], map(Switches[i][SW_STATE], 0, 100, 0, 4096));
    }

    // Debug output (added here to avoid too much load on the serial port):
#ifdef IBUS
    if (!iBUS_VALID)
    {
      DEBUG_PRINTLN("iBUS disconnected!");
    }
#endif
    DEBUG_PRINT("CH5:\t" + String(SIN_POS[RX_CH5][POS]) + "\t\t CH6:\t" + String(SIN_POS[RX_CH6][POS]) + "\t\t SOUT0:\t" + String(SOUT_POS[0]));
    DEBUG_PRINTLN("\t   SW0: " + String(Switches[0][SW_STATE]) + "  SW1: " + String(Switches[1][SW_STATE]) + "  SW2: " + String(Switches[2][SW_STATE]) + "  SW3: " + String(Switches[3][SW_STATE]) + "  SW4: " + String(Switches[4][SW_STATE]) + "  SW5: " + String(Switches[5][SW_STATE]));
  }
}
