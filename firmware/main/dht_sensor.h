#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

// Define the pin and sensor type
#define DHT_PIN 4       // Still wired to D4
#define DHT_TYPE DHT22  // <-- CHANGED TO DHT22

// Initialize the DHT object globally for this module
static DHT dht(DHT_PIN, DHT_TYPE);
bool init_dht() {
  dht.begin();
  Serial.println("Checking DHT22 connection (waiting 2s)...");
  delay(2000); // Sensor needs 2 seconds to stabilize on boot
  
  float test_read = dht.readTemperature();
  if (isnan(test_read)) {
    Serial.println("ERROR: DHT22 not detected! Check wiring.");
    return false;
  }
  
  Serial.println("DHT22 Sensor Initialized successfully.");
  return true;
}

float read_temperature() {
  float temp = dht.readTemperature(); // Reads Celsius
  if (isnan(temp)) {
    Serial.println("Error: Failed to read temperature from DHT22!");
    return -999.0; // Return an obvious error value
  }
  return temp;
}

float read_humidity() {
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Error: Failed to read humidity from DHT22!");
    return -999.0; // Return an obvious error value
  }
  return hum;
}

#endif