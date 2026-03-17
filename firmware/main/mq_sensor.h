#ifndef MQ_SENSOR_H
#define MQ_SENSOR_H

#include <Arduino.h>

// Using ADC1 pin to avoid WiFi conflicts later
#define MQ_PIN 34

bool init_mq() {
  pinMode(MQ_PIN, INPUT);
  
  Serial.println("Checking MQ Gas Sensor...");
  
  // Quick test read to ensure the ADC is responding
  int test_read = analogRead(MQ_PIN);
  
  if (test_read < 0) {
    Serial.println("ERROR: MQ sensor ADC read failed!");
    return false;
  }
  
  Serial.println("MQ Gas Sensor Initialized successfully.");
  Serial.println("NOTE: MQ sensors require a few minutes to heat up and stabilize!");
  return true;
}

int read_mq() {
  // Returns a raw analog value from 0 to 4095
  // Lower values usually mean clean air, higher values mean gas/smoke detected
  return analogRead(MQ_PIN);
}

#endif