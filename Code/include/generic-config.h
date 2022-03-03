/*
*  Generic Settings
*/
#ifndef GENERIC_CONFIG_H
#define GENERIC_CONFIG_H

#include <Arduino.h>

// Firmware Information
#define FIRMWARE_NAME "RC-MultiSwitcher"
#define FIRMWARE_VERSION "1.1.0"

// Serial Output configuration
#define BAUD_RATE 115200
#ifdef SERIAL_OUT
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#endif

#endif //GENERIC_CONFIG_H