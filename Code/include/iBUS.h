/*
*  iBUS header
*/
#ifndef IBUS_H
#define IBUS_H

#ifdef IBUS
// iBUS settings
#define IBUS_CHANNELS 14
#define IBUS_TIMEOUT_MS 50
// iBUS channel mapping
#define IBUS_CH_5 4
#define IBUS_CH_6 5
// Use Teensy Serial3 on Pins SIN0 (RX) and SIN1 (TX - unused)
#define IBUS_SERIAL Serial3
#define IBUS_BPS 115200
#endif

extern uint16_t iBus_readChan(uint8_t ch_num);
extern uint32_t iBus_last_decode;

#endif //IBUS_H