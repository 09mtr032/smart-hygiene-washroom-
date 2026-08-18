# Smart Washroom Hygiene Monitor

## Project Overview
The Smart Washroom Hygiene Monitor is an Arduino Mega based automation project designed to improve washroom hygiene and controlled access.

An IR sensor detects a person entering and the usage count is displayed on a 16x2 I2C LCD. A water pump is activated using a push button for cleaning. A soil moisture sensor detects water/moisture on the floor. The door remains closed until moisture is detected and the user presses the OPEN button.

## Objectives
- Count washroom usage automatically.
- Display the usage count on an LCD.
- Control the door using a servo motor.
- Activate a water pump using a push button.
- Detect water/moisture using a soil moisture sensor.
- Prevent the door from opening before cleaning is completed.
- Provide buzzer alerts and system status.

## Components
- Arduino Mega 2560
- IR Sensor
- 16x2 LCD with I2C module
- Soil Moisture Sensor
- Servo Motor
- DC Water Pump
- Relay Module
- Push Buttons x2
- Buzzer
- Breadboard and jumper wires
- Suitable external power supply

## Pin Connections

| Component | Pin | Arduino Mega |
|---|---|---|
| IR Sensor | OUT | D2 |
| Water Button | One terminal | D3 |
| Open Door Button | One terminal | D4 |
| Buzzer | + | D5 |
| Pump Relay | IN | D6 |
| Servo | Signal | D9 |
| Soil Moisture Sensor | AO | A0 |
| I2C LCD | SDA | D20 / SDA |
| I2C LCD | SCL | D21 / SCL |
| Sensors/LCD/Relay | VCC | 5V |
| Control components | GND | GND |

Both push buttons use INPUT_PULLUP; connect their other terminal to GND.

## Working Principle
1. IR sensor detects a person entering.
2. Arduino increases the washroom usage count.
3. LCD displays the count and system status.
4. Servo keeps the door closed during the cleaning cycle.
5. User presses the WATER button.
6. Relay activates the water pump.
7. Soil moisture sensor checks for water/moisture.
8. When moisture is detected, the pump switches off.
9. Door remains locked.
10. User presses the OPEN button.
11. Arduino checks the moisture condition.
12. If moisture is detected and OPEN is pressed, the servo opens the door.
13. Otherwise, the door remains closed and the buzzer gives a warning.

## Door Opening Condition
`Moisture detected = YES` AND `OPEN button = PRESSED`

## Software
- Arduino IDE
- Arduino Mega 2560 board package
- Wire.h
- LiquidCrystal_I2C
- Servo.h

## Safety
Do not connect the pump directly to an Arduino GPIO pin. Use a suitable relay or MOSFET driver and an appropriate external pump supply. Keep water away from electronics. For AC mains pumps, use proper isolation and qualified electrical installation.

## Future Improvements
- Automatic soap dispenser
- Water-level monitoring
- ESP32/IoT dashboard
- Mobile notifications
- Automatic cleaning timer
- Usage analytics

## Project Outcome
This project demonstrates practical use of sensors, actuators, display modules, buttons, and Arduino programming to create a smart hygiene automation system.
