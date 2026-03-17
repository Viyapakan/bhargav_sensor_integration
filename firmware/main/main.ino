#include "utils.h"

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Initialized. Testing modular LED utilities...");
  
  // 1. Initialize the pin
  init_led();
  
  // 2. Test the toggle function (rapid blink 5 times)
  Serial.println("Executing toggle_led: 5 rapid blinks...");
  toggle_led(5, 200); 
  
  Serial.println("Toggle complete. Moving to main loop.");
}

void loop() {
  // 3. Test the basic on/off functions
  turn_on_led();
  Serial.println("LED is ON");
  delay(1000);
  
  turn_off_led();
  Serial.println("LED is OFF");
  delay(1000);
}