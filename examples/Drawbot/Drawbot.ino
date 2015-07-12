// Make: LEGO and Arduino Projects
// Chapter 1: Drawbot
// Website: http://www.wayneandlayne.com/bricktronics/
//
// Written in 2015 by Matthew Beckler and Adam Wolf for Wayne and Layne, LLC
// To the extent possible under law, the author(s) have dedicated all
//   copyright and related and neighboring rights to this software to the
//   public domain worldwide. This software is distributed without any warranty.
// You should have received a copy of the CC0 Public Domain Dedication along
//   with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 

// Include the Bricktronics motor library and helper libraries
// Helper libraries can be downloaded from:
//      https://www.pjrc.com/teensy/td_libs_Encoder.html
//      https://github.com/br3ttb/Arduino-PID-Library/
//          Be sure to rename unzipped folder PID_v1
#include <Encoder.h>
#include <PID_v1.h>
#include <BricktronicsMotor.h>
// Include the Bricktronics button library
#include <BricktronicsButton.h>

// Include the Bricktronics Shield library and helper libraries
// Requires the Adafruit MCP23017 library:
//      https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <BricktronicsShield.h>


long timeout = 0;

// Create the motor and button objects
BricktronicsMotor r(BricktronicsShield::MOTOR_1); // The r and l Motor objects correspond to the motors plugged into Motor Port 1 and 2, respectively, of the Bricktronics Shield.
BricktronicsMotor l(BricktronicsShield::MOTOR_2);
BricktronicsButton front(BricktronicsShield::SENSOR_1); // The front Button object corresponds to the button plugged into Sensor Port 1.

void setup() // The setup() function is called once, on power on. Here, it’s used to initialize all the Bricktronics objects.
{
    randomSeed(analogRead(A3)); // This line seeds the pseudorandom number generator with an analog reading from a disconnected pin, A3. This helps the numbers be more random.
    BricktronicsShield::begin();
    r.begin();
    l.begin();
    front.begin();
}

void bumpers_hit() // This function is called when the bumpers are hit. The idea is to reverse each motor, and slow it down a bit, but if it slows down too slowly, to start over with new random values, so it doesn’t get boring.
{
    int r_speed = r.getFixedDrive() * -0.9;
    int l_speed = l.getFixedDrive() * -0.9;

    r.setFixedDrive(r_speed);
    l.setFixedDrive(l_speed);
    delay(500);

    if (abs(l_speed) < 25 && abs(r_speed) < 25)
    {
        timeout_expired();
    }
}

void timeout_expired() // This function sets the motors going at a random speed, and it determines a timeout between 1 and 10 seconds, after which it will be called again.
{
    r.setFixedDrive(random(-127, 127));
    l.setFixedDrive(random(-127, 127));

    timeout = millis() + random(1, 10) * 1000;
}

void loop() // In Arduino, your loop() function is called over and over again, until the Arduino runs out of power.
{
    if (timeout != 0 && timeout < millis()) // If the timeout has been set, and the current time is past the timeout, run the timeout_expired() function.
    {
        timeout_expired();
    }

    if (front.isPressed()) // If the front bumper is pressed, then call the bumpers_hit() function, which reverses the robot unless the motors are going too slowly.
    {
        bumpers_hit();
    }
}

