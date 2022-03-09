/*
 * Functions to process Servo INPUT signals
 * to be mapped to the desired switched- and servo OUTPUTS
 */
#include <Arduino.h>
#include "in-out_processing.h"
#include "hardware-config.h"

void Process_RX_CH5()
{
    // SIN0 / RX_CH5 handles lights and water pump; Expecting 0-180°
    if (SIN_POS[RX_CH5][STAT] == 1)
    {
        // Configure outputs according to current position
        switch (SIN_POS[RX_CH5][POS])
        {
        case 0 ... 30:
            // Everything OFF
            Switches[HEADLIGHTS][SW_STATE] = 0;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[SIRENE][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 31 ... 60:
            // Only Headlights ON
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[SIRENE][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 61 ... 90:
            // Headlights and Blue lamp
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 100;
            Switches[SIRENE][SW_STATE] = 0;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 91 ... 120:
            // Headlights, Blue lamp and Sirene
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 100;
            Switches[SIRENE][SW_STATE] = 100;
            Switches[PUMP][SW_STATE] = 0;
            break;

        case 121 ... 150:
            // Headlights, Blue lamp, Sirene and Pump
            Switches[HEADLIGHTS][SW_STATE] = 100;
            Switches[BLUELAMP][SW_STATE] = 100;
            Switches[SIRENE][SW_STATE] = 100;
            Switches[PUMP][SW_STATE] = 50;
            break;

        default:
            // Unhandled position, All off
            Switches[HEADLIGHTS][SW_STATE] = 0;
            Switches[BLUELAMP][SW_STATE] = 0;
            Switches[SIRENE][SW_STATE] = 0;
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
        Switches[SIRENE][SW_STATE] = 0;
    }
}

void Process_RX_CH6()
{
    // SIN1 / RX_CH6 handles winch, percentage input required
    if (SIN_POS[RX_CH6][STAT] == 2)
    {
        // Configure winch output according to current position
        switch (SIN_POS[RX_CH6][POS])
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
