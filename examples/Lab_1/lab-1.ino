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
// *** Light Threshold
// ***
#define LIGHT_THRESHOLD 100

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
    int value = analogRead(LDR_PIN);
    
    // ***
    // *** Chek the vaue read from the analog port
    // *** against the constant threshold value.
    // ***
    if (value < LIGHT_THRESHOLD)
    {
        if (!_ledIsOn)
        {
            // ***
            // *** Turn the LED on.
            // ***
            digitalWrite(LED_PIN, HIGH);
            _ledIsOn = true;
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
        }
    }
    
    // ***
    // *** Short delay before looping...
    // ***
    delay(100);
}