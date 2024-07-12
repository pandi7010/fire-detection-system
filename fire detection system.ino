#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Smoke sensor pins
const int smokeAnalogPin = A0;
const int smokeDigitalPin = 2;

// Threshold value for analog reading (adjust based on your sensor's output)
const int threshold = 300;

// Set to true to use analog pin, false to use digital pin
const bool USE_ANALOG = true;

void setup() {
  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.backlight();
  
  // Initialize the smoke sensor pins
  if (USE_ANALOG) {
    pinMode(smokeAnalogPin, INPUT);
  } else {
    pinMode(smokeDigitalPin, INPUT);
  }
}

void loop() {
  int sensorValue;

  // Read the value from the smoke sensor
  if (USE_ANALOG) {
    sensorValue = analogRead(smokeAnalogPin);
  } else {
    sensorValue = digitalRead(smokeDigitalPin);
  }

  // Clear the previous content on the LCD
  lcd.clear();
  
  if (USE_ANALOG && sensorValue > threshold) {
    // Smoke detected using analog
    lcd.setCursor(0, 0);
    lcd.print("Fire detected");
  } else if (!USE_ANALOG && sensorValue == HIGH) {
    // Smoke detected using digital
    lcd.setCursor(0, 0);
    lcd.print("Fire detected");
  } else {
    // No smoke detected
    lcd.setCursor(0, 0);
    lcd.print("Fire detection");
    lcd.setCursor(0, 1);
    lcd.print("system");
  }
  
  // Small delay to prevent flickering
  delay(500);
}
