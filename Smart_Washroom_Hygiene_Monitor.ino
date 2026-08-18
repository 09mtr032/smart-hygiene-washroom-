/*
  SMART WASHROOM HYGIENE MONITOR
  Board: Arduino Mega 2560

  Door opens only when:
  1. Moisture is detected
  2. OPEN button is pressed
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo doorServo;

const int IR_PIN = 2;
const int WATER_BUTTON = 3;
const int OPEN_BUTTON = 4;
const int BUZZER_PIN = 5;
const int PUMP_RELAY = 6;
const int SERVO_PIN = 9;
const int MOISTURE_PIN = A0;

const int DOOR_CLOSED = 0;
const int DOOR_OPEN = 90;

// Calibrate this value for your moisture sensor.
const int MOISTURE_THRESHOLD = 500;

unsigned long washroomCount = 0;
bool personDetected = false;
bool cleaningStarted = false;
bool moistureDetected = false;

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(WATER_BUTTON, INPUT_PULLUP);
  pinMode(OPEN_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PUMP_RELAY, OUTPUT);

  digitalWrite(PUMP_RELAY, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  doorServo.attach(SERVO_PIN);
  doorServo.write(DOOR_CLOSED);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SMART WASHROOM");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Change HIGH to LOW if your IR module is active-LOW.
  if (digitalRead(IR_PIN) == HIGH && !personDetected) {
    personDetected = true;
    washroomCount++;

    doorServo.write(DOOR_CLOSED);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Person Entered");
    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(washroomCount);

    delay(1000);
  }

  if (digitalRead(IR_PIN) == LOW) {
    personDetected = false;
  }

  // Start water cleaning.
  if (digitalRead(WATER_BUTTON) == LOW) {
    cleaningStarted = true;
    moistureDetected = false;
    digitalWrite(PUMP_RELAY, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cleaning...");
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON");
    delay(300);
  }

  // Detect water/moisture.
  if (cleaningStarted) {
    int moistureValue = analogRead(MOISTURE_PIN);

    // Many modules give a lower value when wet.
    if (moistureValue < MOISTURE_THRESHOLD) {
      moistureDetected = true;
      cleaningStarted = false;
      digitalWrite(PUMP_RELAY, LOW);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cleaning Done");
      lcd.setCursor(0, 1);
      lcd.print("Press OPEN");

      tone(BUZZER_PIN, 2000, 200);
      delay(500);
    }
  }

  // Door opens only after moisture is detected and OPEN is pressed.
  if (digitalRead(OPEN_BUTTON) == LOW) {
    if (moistureDetected) {
      doorServo.write(DOOR_OPEN);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door Opening");
      lcd.setCursor(0, 1);
      lcd.print("Please Enter");

      tone(BUZZER_PIN, 1500, 200);
      delay(1000);

      moistureDetected = false;
    } else {
      doorServo.write(DOOR_CLOSED);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door LOCKED");
      lcd.setCursor(0, 1);
      lcd.print("Cleaning Needed");

      tone(BUZZER_PIN, 1000, 500);
      delay(1000);
    }
  }
}
