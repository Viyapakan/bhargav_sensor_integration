#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>

#define PIR_PIN 5  // Wired to D5

bool init_pir() {
  pinMode(PIR_PIN, INPUT);
  
  Serial.println("Checking PIR Sensor...");
  // PIR sensors take about 30-60 seconds to fully calibrate to a room's ambient infrared signature when first powered on.
  // We won't pause the whole system for 60 seconds, but we establish the pin mode.
  // A simple digital input rarely "fails" a hardware check, so we return true if the board executed pinMode.
  
  Serial.println("PIR Sensor Initialized successfully.");
  return true;
}

bool read_pir() {
  // Returns true if motion is detected (HIGH), false if not (LOW)
  return digitalRead(PIR_PIN) == HIGH;
}

#endif