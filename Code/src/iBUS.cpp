/*
 * iBus Functions
 * NOTE: iBus Code somewhere from the depths of the internet! If you feel like this is your code, please contact me!
 * ATTENTION: None of the available iBUS libraries i've tested worked, just this bunch of code works perfectly well!
 */
#include <Arduino.h>
#include "iBUS.h"
#include "hardware-config.h"

#ifdef IBUS
enum ibus_State
  {
    GET_LENGTH,
    GET_DATA,
    GET_CHKSUML,
    GET_CHKSUMH,
    DISCARD,
  };

static const uint8_t PROTOCOL_LENGTH = 0x20;
static const uint8_t PROTOCOL_OVERHEAD = 3; // <len><cmd><data....><chkl><chkh>
static const uint8_t PROTOCOL_TIMEGAP = 3; // Packets are received every ~7ms so use ~half that for the gap
static const uint8_t PROTOCOL_CHANNELS = IBUS_CHANNELS;
static const uint8_t PROTOCOL_COMMAND40 = 0x40; // Command is always 0x40

uint8_t ibus_state;
uint32_t iBus_last_decode = 0;
uint32_t ibus_last;
uint8_t ibus_buffer[PROTOCOL_LENGTH];
uint8_t ibus_ptr;
uint8_t ibus_len;
uint16_t ibus_channel[PROTOCOL_CHANNELS];
uint16_t ibus_chksum;
uint8_t ibus_lchksum;

uint16_t iBus_readChan(uint8_t ch_num)
{
  if (ch_num < PROTOCOL_CHANNELS)
  {
    return ibus_channel[ch_num];
  }
  else
  {
    return 0;
  }
}

void iBus_loop(void)
{
  while (IBUS_SERIAL.available() > 0)
  {
    uint32_t now = millis();
    if (now - ibus_last >= PROTOCOL_TIMEGAP)
    {
      ibus_state = GET_LENGTH;
    }
    ibus_last = now;
    
    uint8_t v = IBUS_SERIAL.read();
    switch (ibus_state)
    {
      case GET_LENGTH:
        if (v <= PROTOCOL_LENGTH)
        {
          ibus_ptr = 0;
          ibus_len = v - PROTOCOL_OVERHEAD;
          ibus_chksum = 0xFFFF - v;
          ibus_state = GET_DATA;
        }
        else
        {
          ibus_state = DISCARD;
        }
        break;

      case GET_DATA:
        ibus_buffer[ibus_ptr++] = v;
        ibus_chksum -= v;
        if (ibus_ptr == ibus_len)
        {
          ibus_state = GET_CHKSUML;
        }
        break;
        
      case GET_CHKSUML:
        ibus_lchksum = v;
        ibus_state = GET_CHKSUMH;
        break;

      case GET_CHKSUMH:
        // Validate checksum
        if (ibus_chksum == (v << 8) + ibus_lchksum)
        {
          // Execute command - we only know command 0x40
          switch (ibus_buffer[0])
          {
            case PROTOCOL_COMMAND40:
              // Valid - extract channel data
              for (uint8_t i = 1; i < PROTOCOL_CHANNELS * 2 + 1; i += 2)
              {
                ibus_channel[i / 2] = ibus_buffer[i] | (ibus_buffer[i + 1] << 8);
              }
              iBus_last_decode = millis();
              break;

            default:
              break;
          }
        }
        ibus_state = DISCARD;
        break;

      case DISCARD:
      default:
        break;
    }
  }
}

// Arduino framework function to react on received serial data on Serial3
void serialEvent3() {
	iBus_loop();
}
#endif //IBUS