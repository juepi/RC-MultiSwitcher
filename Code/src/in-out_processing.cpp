/*
 * Functions to process Servo INPUT signals
 * to be mapped to the desired switched- and servo OUTPUTS
 */
#include <Arduino.h>
#include "in-out_processing.h"
#include "hardware-config.h"

// Only with IBUS
#ifdef IBUS
void Process_RX_CH3()
{
    // RX_CH3 (Toggle switch) Siren On/Off
    if (SIN_POS[RX_CH3][STAT] == 1)
    {
        // Enable siren if RX_CH3 pressed
        if (SIN_POS[RX_CH3][POS] > 0)
        {
            Switches[SIREN][SW_STATE] = 100;
        }
        else
        {
            Switches[SIREN][SW_STATE] = 0;
        }
    }
    else
    {
        // Servo INPUT signal invalid, stop winch
        SOUT_POS[WINCH] = 90;
    }
}
#endif // IBUS

void Process_RX_CH5()
{
    // SIN0 / RX_CH5 handles lights and water pump; Expecting 0-180°
    if (SIN_POS[RX_CH5][STAT] == 1)
    {
        // Configure outputs according to current position
        switch ((int)SIN_POS[RX_CH5][POS])
        {
        case 0 ... 30:
            // Everything OFF
            Switches[HEADLIGHTS][SW_STATE] = 0;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 31 ... 60:
            // Only Headlights ON
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 61 ... 90:
            // Headlights and Blue lamp
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 100;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 91 ... 180:
            // Headlights, Blue lamp and Pump
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 100;
            // Map pump power according to RX_CH5 position
            Switches[PUMP][SW_STATE] = (short)map(SIN_POS[RX_CH5][POS], 91, 180, PUMP_MIN_PWM, PUMP_MAX_PWM);
            break;

        default:
            // Unhandled position, All off
            Switches[HEADLIGHTS][SW_STATE] = 0;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;
        }
    }
    else
    {
        // Servo INPUT signal invalid, turn off everything
        Switches[HEADLIGHTS][SW_STATE] = 0;
        Switches[BLUELAMP][SW_STATE] = 0;
        Switches[PUMP][SW_STATE] = 0;
    }
}

void Process_RX_CH6()
{
    // SIN1 / RX_CH6 handles winch, percentage input required
    if (SIN_POS[RX_CH6][STAT] == 2)
    {
        // Configure winch output according to current position
        switch ((int)SIN_POS[RX_CH6][POS])
        {
        case -100 ... - 30:
            // Map "reverse" input to 0..89°
            SOUT_POS[WINCH] = (short)map(SIN_POS[RX_CH6][POS], -100, -30, 0, 89);
            break;

        case 31 ... 100:
            // Map "forward" input to 91..180°
            SOUT_POS[WINCH] = (short)map(SIN_POS[RX_CH6][POS], 31, 100, 91, 180);
            break;

        default:
            // Everything else stops the winch
            // this results in a wide neutral (off) range
            // so you don't have to hit the neutral position on your TX very exactly (rotating knob)
            SOUT_POS[WINCH] = 90;
            break;
        }
    }
    else
    {
        // Servo INPUT signal invalid, stop winch
        SOUT_POS[WINCH] = 90;
    }
}
