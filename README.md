# Overview

In this project, we intend to build an automated plant watering system according to
the presence of sunlight and soil moisture. To detect the presence of sunlight and
moisture in soil, a `Light Dependent Resistor (LDR)` and `Soil Moisture Sensor` will
be used. The system will read the moisture value of the soil using a soil moisture
sensor and will also read the output voltage value from the LDR. Then, according
to that, a `Micro Pump` will be turned on or off through a `Relay Switch` to water the plant.
Alongside that, an `Ultrasonic Sensor` and a `Passive Buzzer` will be used to alert the user if
there is some sort of water overflow or water clot due to an error in the system or
due to nature. Also, relevant information about the whole system regarding the
sensors and the pump will be indicated by a `16X2 I2C LCD Display`. The whole
automated system will be controlled by an `Arduino Uno R3 Microcontroller`.

# Tools

+ Arduino IDE
+ Tinkercad
+ Arduino Uno R3 (ATmega328)
+ 1 Channel 5V Relay Board Module
+ 5V Submersible Micro Pump
+ Transparent Pipe for Pump
+ 20 mm LDR (Light Dependent Resistor)
+ YL-69 Soil Moisture Sensor
+ HC-SR04 Ultrasonic Sonar Sensor
+ 5V Passive Buzzer
+ 16x2 Standard LCD Module Display with Soldered I2C Adapter Board
+ Jumper Wires (Male-to-Female & Male-to-Male)
+ MB102 Large Breadboard
+ Resistors (470 Ohm & 1 KOhm)
+ Soil

# Language

+ C++ Variant

# Tinkercad Diagram
-[Tinkercad](https://www.tinkercad.com/things/6y1Dqi0Ej4s-copy-of-cse360projectplant-watering-system/editel?returnTo=%2Fthings%2F6y1Dqi0Ej4s-copy-of-cse360projectplant-watering-system&sharecode=WjTpDR0t9NABc8VRIjOwo-iBrnUwc8eK2Aa46AoLg7E)
