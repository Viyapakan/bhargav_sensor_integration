#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#include <Arduino.h>

// Using ADC1 pin D35 for safe WiFi compatibility
#define SOUND_PIN 35

bool init_sound() {
  pinMode(SOUND_PIN, INPUT);
  
  Serial.println("Checking Sound Sensor...");
  
  int test_read = analogRead(SOUND_PIN);
  
  if (test_read < 0) {
    Serial.println("ERROR: Sound sensor ADC read failed!");
    return false;
  }
  
  Serial.println("Sound Sensor Initialized successfully.");
  return true;
}

int read_sound() {
  // Returns a raw analog value representing noise level (0 to 4095)
  return analogRead(SOUND_PIN);
}

#endif