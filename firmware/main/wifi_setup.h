#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <Arduino.h>
#include <WiFi.h>

// --- REPLACE THESE WITH YOUR ACTUAL WIFI CREDENTIALS ---
const char* ssid = "viya_2G_router";
const char* password = "Viyanu24%";

bool init_wifi() {
  Serial.print("Connecting to WiFi network: [");
  Serial.print(ssid);
  Serial.println("]...");

  // Set WiFi to station mode (connecting to a router, not creating its own network)
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  int attempts = 0;
  // Try to connect for 10 seconds (20 attempts * 500ms)
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println(); // Print a new line after the dots

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected successfully!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("ERROR: WiFi Connection Failed or Timed Out! Check credentials.");
    return false;
  }
}

#endif