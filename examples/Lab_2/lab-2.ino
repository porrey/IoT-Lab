// Copyright © 2018 Daniel Porrey. All Rights Reserved.
//
// This file is part of the IoT Labs library.
// 
// IoT Labs library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// IoT Labs library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with IoT Labs library. If not, 
// see http://www.gnu.org/licenses/.
//

// ***
// *** Allow the Tinker application to work with this application.
// ***
#include "Tinker.h"

// ***
// *** Light Threshold
// ***
int _lightThreshold = 150;

// ***
// *** Last read light level.
// ***
int _lightLevel = 0;

// ***
// *** Specifies the pin on which the LDR is connected.
// ***
#define LDR_PIN A0

// ***
// *** Specifies the pin on which the LED is connected.
// ***
#define LED_PIN D0

// ***
// *** Track the state of the LED.
// ***
bool _ledIsOn = false;

void setup() 
{
    // ***
    // *** Register all the Tinker functions.
    // ***
	Particle.function("digitalread", tinkerDigitalRead);
	Particle.function("digitalwrite", tinkerDigitalWrite);
	Particle.function("analogread", tinkerAnalogRead);
	Particle.function("analogwrite", tinkerAnalogWrite);
	
	// ***
	// *** Register the application functions and variables.
	// ***
	Particle.variable("threshold", _lightThreshold);
	Particle.function("setThreshold", _SetThreshold);
	Particle.variable("lightLevel", _lightLevel);
	
    // ***
    // *** Get the LED pin ready for output.
    // ***
    pinMode(LED_PIN, OUTPUT);
    
    // ***
    // *** Initialize the LED to off.
    // ***
    digitalWrite(LED_PIN, LOW);
    _ledIsOn = false;
}

void loop() 
{
    // ***
    // *** Read the analog pin.
    // ***
    _lightLevel = analogRead(LDR_PIN);
    
    // ***
    // *** Chek the vaue read from the analog port
    // *** against the current threshold value.
    // ***
    if (_lightLevel < _lightThreshold)
    {
        if (!_ledIsOn)
        {
            // ***
            // *** Turn the LED on.
            // ***
            digitalWrite(LED_PIN, HIGH);
            _ledIsOn = true;
            
            // ***
            // *** Publish a cloud message.
            // ***
            Particle.publish("LED", "on");
        }
    }
    else 
    {
        if (_ledIsOn)
        {
            // ***
            // *** Turn the LED off.
            // ***
            digitalWrite(LED_PIN, LOW);
            _ledIsOn = false;
            
            // ***
            // *** Publish a cloud message.
            // ***
            Particle.publish("LED", "off");
        }
    }
    
    // ***
    // *** Short delay before looping...
    // ***
    delay(500);
}

int _SetThreshold(String data)
{
    _lightThreshold = data.toInt();
    return _lightThreshold;
}