# BricktronicsShield API

This meta-library provides easy interfacing to the [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html). This library does not contain any functional code for motors or sensors, rather it provides static mappings between motor and sensor ports on the Shield, and the pin numbers needed by the motor and sensor libraries. It packages the pin settings into two structs defined in [BricktronicsSettings.h](utility/BricktronicsSettings.h), which are defined as static const objects in the BricktronicsMegashield class. Use these objects in your motor and sensor constructors. Since the Bricktronics Shield uses an I/O expander chip to add additional pins, this library does contain the code needed to interface with that chip, and provide a way for the motor and sensor libraries to transparently talk to that chip.

# Supported motor and sensor libraries

* [BricktronicsMotor](https://github.com/wayneandlayne/BricktronicsMotor) – Support for NXT 2.0 and EV3 servomotors
* [BricktronicsLight](https://github.com/wayneandlayne/BricktronicsLight) – Support for monochrome light sensor
* [BricktronicsColor](https://github.com/wayneandlayne/BricktronicsColor) – Support for color sensors
* [BricktronicsSound](https://github.com/wayneandlayne/BricktronicsSound) – Support for sound sensors
* [BricktronicsButton](https://github.com/wayneandlayne/BricktronicsButton) – Support for pushbutton sensors
* [BricktronicsUltrasonic](https://github.com/wayneandlayne/BricktronicsUltrasonic) – Support for the NXT 2.0 ultrasonic sensor

# Quick Example

Use the BricktronicsShied library to provide details on the pin connections for a pushbutton sensor to any sensor port on the Bricktronics Shield. If the chosen sensor port has jumpers, use them to connect pins 2-3 and 4-5.

```C++
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <BricktronicsShield.h>
#include <BricktronicsButton.h>

// Declare the sensor is connected to sensor port 1
BricktronicsButton b(BricktronicsShield::SENSOR_1);

void setup()
{
    Serial.begin(115200);

    // Need to call this to initialize the BricktronicsShield
    BricktronicsShield::begin();

    b.begin();
}

void loop()
{
    delay(500);
    while(b.isReleased());
    Serial.println("pressed");
    delay(100);

    while(b.isPressed());
    Serial.println("released");
    delay(100);
}
```

# Motor settings

#### `BricktronicsShield::MOTOR_1`
#### `BricktronicsShield::MOTOR_2`

# Sensor settings

#### `BricktronicsShield::SENSOR_1`
#### `BricktronicsShield::SENSOR_2`
#### `BricktronicsShield::SENSOR_3`
#### `BricktronicsShield::SENSOR_4`

# Interface to MCP23017 I/O Expander Chip

#### `static void BricktronicsShield::pinMode(uint8_t pin, uint8_t mode)`

Configures the specified pin to behave either as an input or an output pin. If `pin` is 64 or greater, configure pin `(pin - 64)` on MCP23017 chip, otherwise call the default [Arduino pinMode function](https://www.arduino.cc/en/Reference/PinMode). Valid options for `mode` are `INPUT`, `OUTPUT`, or `INPUT_PULLUP`.

#### `static void BricktronicsShield::digitalWrite(uint8_t pin, uint8_t level)`

Write a HIGH or a LOW value to a digital pin. If `pin` is 64 or greater, write to pin `(pin - 64)` on MCP23017 chip, otherwise call the default [Arduino digitalWrite function](https://www.arduino.cc/en/Reference/DigitalWrite). Valid options for `level` are `HIGH` or `LOW`.

#### `static void BricktronicsShield::digitalRead(uint8_t pin)`

Reads the value from a specified digital pin. If `pin` is 64 or greater, read from pin `(pin - 64)` on MCP23017 chip, otherwise call the default [Arduino digitalRead function](https://www.arduino.cc/en/Reference/DigitalRead). Returns either `HIGH` or `LOW`.

# Enumerations and constants

#### TIP-120 pin constants

* `BS_TIP_0` - Drives the TIP-120 connected to header EXT1
* `BS_TIP_1` - Drives the TIP-120 connected to header EXT2
