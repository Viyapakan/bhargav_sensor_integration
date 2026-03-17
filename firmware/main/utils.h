#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

// Define the built-in LED pin
const int LED_PIN = 2;

// Initialize the LED pin (call this in setup)
void init_led() {
  pinMode(LED_PIN, OUTPUT);
}

// Turn LED on
void turn_on_led() {
  digitalWrite(LED_PIN, HIGH);
}

// Turn LED off
void turn_off_led() {
  digitalWrite(LED_PIN, LOW);
}

// Toggle LED a specific number of times with a custom delay
void toggle_led(int times, int delay_ms) {
  for (int i = 0; i < times; i++) {
    turn_on_led();
    delay(delay_ms);
    turn_off_led();
    delay(delay_ms);
  }
}

#endif