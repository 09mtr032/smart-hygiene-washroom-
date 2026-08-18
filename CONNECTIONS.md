# Circuit Connections

## Arduino Mega Pin Map

| Arduino Mega Pin | Device |
|---|---|
| D2 | IR Sensor OUT |
| D3 | Water Pump Button |
| D4 | Open Door Button |
| D5 | Buzzer |
| D6 | Relay IN |
| D9 | Servo Signal |
| A0 | Soil Moisture Sensor AO |
| D20 | I2C LCD SDA |
| D21 | I2C LCD SCL |
| 5V | Low-voltage module power |
| GND | Common control ground |

## I2C LCD
- VCC -> Arduino Mega 5V
- GND -> Arduino Mega GND
- SDA -> Arduino Mega D20
- SCL -> Arduino Mega D21

## Buttons
Both buttons use INPUT_PULLUP.
- Water Button: D3 to GND
- Open Door Button: D4 to GND

## Pump
Arduino D6 controls the relay module. The pump must use a suitable external power supply. Never power the pump from an Arduino GPIO pin.
