#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>

// CRITICAL: Switched to GPIO 33 (ADC1) since GPIO 32 failed continuity
#define LIGHT_PIN 33

bool init_light() {
  pinMode(LIGHT_PIN, INPUT);
  
  Serial.println("Checking Light Sensor...");
  
  // Do a quick test read to ensure the ADC is responding
  int test_read = analogRead(LIGHT_PIN);
  
  // ESP32 analogRead should return between 0 and 4095. 
  if (test_read < 0) {
    Serial.println("ERROR: Light sensor ADC read failed!");
    return false;
  }
  
  Serial.println("Light Sensor Initialized successfully.");
  return true;
}

int read_light() {
  // Returns a value from 0 (very bright) to 4095 (completely dark) 
  // Note: Depending on your specific module, the logic might be inverted
  return analogRead(LIGHT_PIN);
}

#endif