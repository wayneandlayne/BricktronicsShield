/*
   BricktronicsShield v1.2 - A software library for Bricktronics Shield.
   This library is only needed if you are using a Bricktronics Shield.
   If you are using a break-out board or a motor driver board,
   you can just directly use the motor and sensor libraries.

   Copyright (C) 2015 Adam Wolf, Matthew Beckler, John Baichtal

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

   Wayne and Layne invests time and resources providing this open-source
   code, please support W&L and open-source hardware by purchasing products
   from https://store.wayneandlayne.com/ - Thanks!

   Wayne and Layne, LLC and our products are not connected to or endorsed by the LEGO Group.
   LEGO, Mindstorms, and NXT are trademarks of the LEGO Group.
*/

#ifndef BRICKTRONICSSHIELD_H
#define BRICKTRONICSSHIELD_H

// Header files
#include <inttypes.h>
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "utility/BricktronicsSettings.h"

// Pins above 64 are assigned to the IO expander pins.
// We can just mask away upper bits to "subtract 64" in that case.
#define BS_PIN_MASK   0x3F

// Defines for the Bricktronics Shield - Uses an IO expander chip, which corresponds to pins > 64
#define BS_TIP_0                11
#define BS_TIP_1                71

class BricktronicsShield
{
    public:
        // Empty constructor that we never use, since everything is static.
        BricktronicsShield();

        static void begin(void);

        // Bricktronics Shield motor settings
        static const BricktronicsMotorSettings MOTOR_1;
        static const BricktronicsMotorSettings MOTOR_2;

        // Bricktronics Shield sensor settings
        static const BricktronicsSensorSettings SENSOR_1;
        static const BricktronicsSensorSettings SENSOR_2;
        static const BricktronicsSensorSettings SENSOR_3;
        static const BricktronicsSensorSettings SENSOR_4;

        // These version of the standard low-level Arduino functions
        // check to see if the referenced pin is > 64 (indicating that
        // the pin is accessed via the MCP I/O expander chip). If so,
        // the pin operation is delegated to the MCP chip, otherwise the
        // standard Arduino version of the function is called.
        static void pinMode(uint8_t pin, uint8_t mode);
        static void digitalWrite(uint8_t pin, uint8_t level);
        static int digitalRead(uint8_t pin);

    //private:
        static Adafruit_MCP23017 _mcp;
};

#endif // #ifndef BRICKTRONICSSHIELD_H

