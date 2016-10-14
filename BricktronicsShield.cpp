/*
   BricktronicsShield v1.2 - A software library for Bricktronics Shield.
   This library is only needed if you are using a Bricktronics Shield.
   If you are using a break-out board or a motor driver board,
   you can just directly use the motor and sensor libraries.

   Copyright (C) 2016 Adam Wolf, Matthew Beckler, John Baichtal

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

#include "BricktronicsShield.h"

// Motor settings
const BricktronicsMotorSettings BricktronicsShield::MOTOR_1 = {
    79, // enPin
    78, // dirPin
    10, // pwmPin
    2,  // encoderPin1
    5,  // encoderPin2
    true, // reversedMotorDrive
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};

const BricktronicsMotorSettings BricktronicsShield::MOTOR_2 = {
    77, // enPin
    76, // dirPin
    9,  // pwmPin
    3,  // encoderPin1
    4,  // encoderPin2
    true, // reversedMotorDrive
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};


// Sensor settings
const BricktronicsSensorSettings BricktronicsShield::SENSOR_1 = {
    A0, // ANA
    70, // DA
    69, // DB
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};

const BricktronicsSensorSettings BricktronicsShield::SENSOR_2 = {
    A1, // ANA
    68, // DA
    67, // DB
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};

const BricktronicsSensorSettings BricktronicsShield::SENSOR_3 = {
    A2, // ANA
    8,  // DA
    12, // DB
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};

const BricktronicsSensorSettings BricktronicsShield::SENSOR_4 = {
    A3, // ANA
    7,  // DA
    6,  // DB
    &BricktronicsShield::pinMode,
    &BricktronicsShield::digitalWrite,
    &BricktronicsShield::digitalRead,
};


Adafruit_MCP23017 BricktronicsShield::_mcp;

void BricktronicsShield::begin()
{
    Wire.begin();
    _mcp.begin();
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)
    // Set timer1 frequency to about 32 kHz to reduce audible whine with PWM
    TCCR1B = (TCCR1B & 0b11111000) | 0x01;
#endif
// TODO - Do the same thing for Mega2560 if we want
}

void BricktronicsShield::pinMode(uint8_t pin, uint8_t mode)
{
    // There is a bit of a tricky spot here.
    // In normal Arduino world, pinMode accepts these modes:
    //     INPUT, OUTPUT, INPUT_PULLUP
    // In MCP I/O expander world, pinMode only handles I vs O,
    //     and we have to separately call _mcp.pullUp to turn on
    //     pullup resistors.
    if (pin < 64)
    {
        ::pinMode(pin, mode);
    }
    else
    {
        // Strip away the upper bits - Same as subtracting 64.
        uint8_t newPin = pin & BS_PIN_MASK;
        if (mode == OUTPUT)
        {
            _mcp.pinMode(newPin, OUTPUT);
            _mcp.pullUp(newPin, LOW);
        }
        else
        {
            // either INPUT or INPUT_PULLUP
            _mcp.pinMode(newPin, INPUT);
            if (mode == INPUT_PULLUP)
            {
                _mcp.pullUp(newPin, HIGH);
            }
            else
            {
                _mcp.pullUp(newPin, LOW);
            }
        }
    }
}

void BricktronicsShield::digitalWrite(uint8_t pin, uint8_t level)
{
    if (pin < 64)
    {
        ::digitalWrite(pin, level);
    }
    else
    {
        _mcp.digitalWrite(pin & BS_PIN_MASK, level);
    }
}

int BricktronicsShield::digitalRead(uint8_t pin)
{
    if (pin < 64)
    {
        return( ::digitalRead(pin) );
    }
    else
    {
        return( _mcp.digitalRead(pin & BS_PIN_MASK) );
    }
}

