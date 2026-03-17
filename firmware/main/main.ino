#include "utils.h"
#include "dht_sensor.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- System Booting ---");
  
  bool system_ok = true;

  // 1. Init LED
  if (!init_led()) {
    Serial.println("INIT FAILED: LED Module");
    system_ok = false;
  }

  // 2. Init DHT22
  if (!init_dht()) {
    Serial.println("INIT FAILED: DHT22 Module");
    system_ok = false;
  }

  // 3. Final System Check
  if (system_ok) {
    Serial.println("DEBUG: All systems initiated successfully!");
    toggle_led(3, 100); // 3 rapid blinks for success
  } else {
    Serial.println("DEBUG: System initialization HALTED due to hardware errors.");
    while (1) {
      // Infinite error loop: Blink the LED slowly to indicate a hardware fault
      turn_on_led(); delay(500); turn_off_led(); delay(500);
    }
  }
}

void loop() {
  // Read the data
  float temperature = read_temperature();
  float humidity = read_humidity();

  // Print the data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  delay(2000); 
}