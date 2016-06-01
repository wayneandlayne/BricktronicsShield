BricktronicsShield
==================

**BricktronicsShield v1.2 - A software library for Arduino.**

This meta-library provides easy interfacing to the [Bricktronics Shield](https://store.wayneandlayne.com/products/bricktronics-shield-kit.html). This library does not contain any functional code for motors or sensors, rather it provides static mappings between motor and sensor ports on the Shield, and the pin numbers needed by the motor and sensor libraries. It packages the pin settings into two structs defined in [BricktronicsSettings.h](utility/BricktronicsSettings.h), which are defined as static const objects in the BricktronicsMegashield class. Use these objects in your motor and sensor constructors. Since the Bricktronics Shield uses an I/O expander chip to add additional pins, this library does contain the code needed to interface with that chip, and provide a way for the motor and sensor libraries to transparently talk to that chip.

More details at http://www.wayneandlayne.com/bricktronics/

**To Download**
Click the "Clone or download" button on the upper-right side of this page below the pink bar, then select "Download ZIP". Rename the uncompressed folder BricktronicsShield. Check that the BricktronicsShield folder contains BricktronicsShield.cpp and BricktronicsShield.h

Place the BricktronicsShield library folder into your `<arduinosketchfolder>/libraries/` folder. You may need to create the libraries subfolder if this is your first installed library. Restart the Arduino IDE.

**This library depends on the following other Arduino libraries:**
* [Adafruit's MCP23017 I2C Port Expander Arduino Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)

**API Highlights**
* `BricktronicsShield::MOTOR_1` - Use this static const struct in your motor constructors. `MOTOR_1` through `MOTOR_2` are defined.
* `BricktronicsShield::SENSOR_1` - Use this static const struct in your sensor constructors. `SENSOR_1` through `SENSOR_4` are defined.
* More API details in [API.md](API.md)

**Supported motor and sensor libraries you may be interested in:**
* [BricktronicsMotor](https://github.com/wayneandlayne/BricktronicsMotor) – Support for NXT 2.0 and EV3 servomotors
* [BricktronicsLight](https://github.com/wayneandlayne/BricktronicsLight) – Support for monochrome light sensor
* [BricktronicsColor](https://github.com/wayneandlayne/BricktronicsColor) – Support for color sensors
* [BricktronicsSound](https://github.com/wayneandlayne/BricktronicsSound) – Support for sound sensors
* [BricktronicsButton](https://github.com/wayneandlayne/BricktronicsButton) – Support for pushbutton sensors
* [BricktronicsUltrasonic](https://github.com/wayneandlayne/BricktronicsUltrasonic) – Support for the NXT 2.0 ultrasonic sensor

_Wayne and Layne, LLC and our products are not connected to or endorsed by the LEGO Group. LEGO, Mindstorms, and NXT are trademarks of the LEGO Group._

