/* Copyright (c) Intel. All rights reserved.
Licensed under the MIT license. See LICENSE file in the project root for full license information.
*/

/*
  Grove LCD

  Example using the Grove LCD UPM library. Prints the value of the analog input from the Grove Rotary Angle Sensor to the display.

  https://github.com/intel-iot-devkit/up-squared-grove-IoT-dev-kit-arduino-create/tree/master/examples/GroveLCD
*/

// upm - Version: Latest 
//#include <ArduinoUPM.h>
//#include <jhd1313m1.hpp>

#include <jhd1313m1.h>
#include "upm_utilities.h"

jhd1313m1_context lcd;

int ndx = 0;
char str[32];
uint8_t rgb[7][3] = {
    {0xd1, 0x00, 0x00},
    {0xff, 0x66, 0x22},
    {0xff, 0xda, 0x21},
    {0x33, 0xdd, 0x00},
    {0x11, 0x33, 0xcc},
    {0x22, 0x00, 0x66},
    {0x33, 0x00, 0x44}};

void setup() {
    DebugSerial.begin(9600);

    lcd = jhd1313m1_init(0, 0x3e, 0x62);

    if (!lcd) 
        DebugSerial.println("jhd1313m1_i2c_init() failed.");
}

void loop() {
    snprintf(str, sizeof(str), "Hello World %d\0", ndx);
    // Alternate rows on the LCD
    jhd1313m1_set_cursor(lcd, ndx%2, 0);
    jhd1313m1_write(lcd, str, strlen(str));
    // Change the color
    uint8_t r = rgb[ndx%7][0];
    uint8_t g = rgb[ndx%7][1];
    uint8_t b = rgb[ndx%7][2];
    jhd1313m1_set_color(lcd, r, g, b);
    // Echo via DebugSerial
    snprintf(str, sizeof(str), "Hello World %d rgb: 0x%02x%02x%02x\0", ndx++, r, g, b);
    DebugSerial.println(str);
    upm_delay(1);
}