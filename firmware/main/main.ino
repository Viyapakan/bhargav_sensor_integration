#include "utils.h"
#include "dht_sensor.h"
#include "pir_sensor.h"
#include "light_sensor.h"
#include "mq_sensor.h"
#include "sound_sensor.h"
#include "ir_sensor.h" // <-- NEW INCLUSION

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- System Booting ---");
  
  bool system_ok = true;

  if (!init_led()) { Serial.println("INIT FAILED: LED Module (Pin 2)"); system_ok = false; }
  if (!init_dht()) { Serial.println("INIT FAILED: DHT22 Module (Pin 4)"); system_ok = false; }
  if (!init_pir()) { Serial.println("INIT FAILED: PIR Module (Pin 5)"); system_ok = false; }
  if (!init_light()) { Serial.println("INIT FAILED: Light Sensor Module (Pin 33)"); system_ok = false; }
  if (!init_mq()) { Serial.println("INIT FAILED: MQ Gas Sensor Module (Pin 34)"); system_ok = false; }
  if (!init_sound()) { Serial.println("INIT FAILED: Sound Sensor Module (Pin 35)"); system_ok = false; }
  
  // Init IR Sensors
  if (!init_ir_one()) { 
    Serial.println("INIT FAILED: IR Sensor One (Pin 18)"); 
    system_ok = false; 
  }
  if (!init_ir_two()) { 
    Serial.println("INIT FAILED: IR Sensor Two (Pin 19)"); 
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
  // Read all sensors
  float temperature = read_temperature();
  float humidity = read_humidity();
  int light_level = read_light();
  int gas_level = read_mq();
  int sound_level = read_sound();
  
  bool motion_detected = read_pir();
  bool ir1_blocked = read_ir_one();
  bool ir2_blocked = read_ir_two();

  // Print Analog/Data values
  Serial.print("T:"); Serial.print(temperature, 1);
  Serial.print("C | H:"); Serial.print(humidity, 1);
  Serial.print("% | Lgt:"); Serial.print(light_level);
  Serial.print(" | Gas:"); Serial.print(gas_level);
  Serial.print(" | Snd:"); Serial.print(sound_level);
  
  // Print Digital Triggers safely at the end
  Serial.print(" || TRIGGERS -> PIR:");
  Serial.print(motion_detected ? "[YES]" : "[no] ");
  
  Serial.print(" | IR1:");
  Serial.print(ir1_blocked ? "[BLOCKED]" : "[clear]  ");
  
  Serial.print(" | IR2:");
  Serial.println(ir2_blocked ? "[BLOCKED]" : "[clear]  ");

  delay(2000); 
}