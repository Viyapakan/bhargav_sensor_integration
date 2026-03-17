#include "utils.h"
#include "dht_sensor.h"
#include "pir_sensor.h"
#include "light_sensor.h"
#include "mq_sensor.h"
#include "sound_sensor.h"
#include "ir_sensor.h"
#include "wifi_setup.h" // <-- NEW INCLUSION

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- System Booting ---");
  
  bool system_ok = true;

  // 1. Hardware Checks
  if (!init_led()) { Serial.println("INIT FAILED: LED Module"); system_ok = false; }
  if (!init_dht()) { Serial.println("INIT FAILED: DHT22 Module"); system_ok = false; }
  if (!init_pir()) { Serial.println("INIT FAILED: PIR Module"); system_ok = false; }
  if (!init_light()) { Serial.println("INIT FAILED: Light Sensor Module"); system_ok = false; }
  if (!init_mq()) { Serial.println("INIT FAILED: MQ Gas Sensor Module"); system_ok = false; }
  if (!init_sound()) { Serial.println("INIT FAILED: Sound Sensor Module"); system_ok = false; }
  if (!init_ir_one()) { Serial.println("INIT FAILED: IR Sensor One"); system_ok = false; }
  if (!init_ir_two()) { Serial.println("INIT FAILED: IR Sensor Two"); system_ok = false; }

  // 2. Network Check
  // We only attempt WiFi if the hardware is healthy!
  if (system_ok) {
    if (!init_wifi()) {
      Serial.println("INIT FAILED: WiFi Network");
      system_ok = false;
    }
  }

  // 3. Final Verdict
  if (system_ok) {
    Serial.println("=========================================");
    Serial.println("ALL SYSTEMS ONLINE. COMMENCING DATA LOOP.");
    Serial.println("=========================================");
    toggle_led(3, 100); 
  } else {
    Serial.println("=========================================");
    Serial.println("SYSTEM HALTED DUE TO ERRORS.");
    Serial.println("=========================================");
    while (1) { turn_on_led(); delay(500); turn_off_led(); delay(500); }
  }
}

void loop() {
  float temperature = read_temperature();
  float humidity = read_humidity();
  int light_level = read_light();
  int gas_level = read_mq();
  int sound_level = read_sound();
  
  bool motion_detected = read_pir();
  bool ir1_blocked = read_ir_one();
  bool ir2_blocked = read_ir_two();

  Serial.print("T:"); Serial.print(temperature, 1);
  Serial.print("C | H:"); Serial.print(humidity, 1);
  Serial.print("% | Lgt:"); Serial.print(light_level);
  Serial.print(" | Gas:"); Serial.print(gas_level);
  Serial.print(" | Snd:"); Serial.print(sound_level);
  
  Serial.print(" || PIR:"); Serial.print(motion_detected ? "[YES]" : "[no] ");
  Serial.print(" | IR1:"); Serial.print(ir1_blocked ? "[BLK]" : "[clr]");
  Serial.print(" | IR2:"); Serial.println(ir2_blocked ? "[BLK]" : "[clr]");

  delay(2000); 
}