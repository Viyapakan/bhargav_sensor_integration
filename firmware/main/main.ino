#include "utils.h"
#include "dht_sensor.h"
#include "pir_sensor.h"
#include "light_sensor.h" // <-- NEW INCLUSION

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- System Booting ---");
  
  bool system_ok = true;

  if (!init_led()) { Serial.println("INIT FAILED: LED Module"); system_ok = false; }
  if (!init_dht()) { Serial.println("INIT FAILED: DHT22 Module"); system_ok = false; }
  if (!init_pir()) { Serial.println("INIT FAILED: PIR Module"); system_ok = false; }
  
  // Init Light Sensor
  if (!init_light()) { 
    Serial.println("INIT FAILED: Light Sensor Module"); 
    system_ok = false; 
  }

  if (system_ok) {
    Serial.println("DEBUG: All systems initiated successfully!");
    toggle_led(3, 100); 
  } else {
    Serial.println("DEBUG: System initialization HALTED due to hardware errors.");
    while (1) { turn_on_led(); delay(500); turn_off_led(); delay(500); }
  }
}

void loop() {
  float temperature = read_temperature();
  float humidity = read_humidity();
  bool motion_detected = read_pir();
  int light_level = read_light(); // <-- NEW READ

  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" *C | Hum: "); Serial.print(humidity);
  Serial.print(" % | Light: "); Serial.print(light_level); // <-- PRINT LIGHT
  
  Serial.print(" | Motion: ");
  if (motion_detected) {
    Serial.println("DETECTED! [###]");
  } else {
    Serial.println("None");
  }

  delay(2000); 
}