// Getting started with Lego and Arduino
// Chapter 7: GripperBot: Tank Base
// Website: http://www.wayneandlayne.com/bricktronics
//
// Written in 2016 by Matthew Beckler and Adam Wolf for Wayne and Layne, LLC
// To the extent possible under law, the author(s) have dedicated all
//   copyright and related and neighboring rights to this software to the
//   public domain worldwide. This software is distributed without any warranty.
// You should have received a copy of the CC0 Public Domain Dedication along
//   with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>. 


// Include the Bricktronics libraries
#include <BricktronicsShield.h>
#include <BricktronicsMotor.h>


// Create the motor objects
BricktronicsMotor r(BricktronicsShield::MOTOR_1);
BricktronicsMotor l(BricktronicsShield::MOTOR_2);

void setup() // The setup() function runs once at startup.
{
    Serial.begin(9600);
    BricktronicsShield::begin();
    r.begin();
    l.begin();
}

void process_incoming_command(char cmd, char arg0) // takes in the two bytes of the body of a command, and then performs the specified action.
{
    int speed = 0;
    switch (cmd)
    {
        case '6':
        case 6: // If the command was "set the speed to motor 6 (left tank tread)," then the code that follows is run.
            speed = arg0*2;
            l.setFixedDrive(speed);
            break;
        case '7':
        case 7: // If the command was "set the speed to motor 7 (right tank tread)," the code that follows is run.
            speed = arg0*2;
            r.setFixedDrive(speed);
            break;
        default:
            break;
    }
}

void loop()
{
    while (Serial.available() < 3)
    {
        //Do nothing while we wait for a full command to come in.
    }
    char start = Serial.read(); // Remove the oldest character from the serial buffer, and put it into start.
    if (start != '*') // This isn't the start of the command, so let's try the next one.
    {
        return; // Start back over at the top of loop().
    }

    char cmd = Serial.read(); // Read the command and argument, and call process_incoming_command().
    char arg0 = Serial.read();
    process_incoming_command(cmd, arg0);
}

