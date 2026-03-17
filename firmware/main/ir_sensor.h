#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>

#define IR_ONE_PIN 18
#define IR_TWO_PIN 19

bool init_ir_one() {
  pinMode(IR_ONE_PIN, INPUT);
  Serial.print("Checking IR Sensor One (Pin ");
  Serial.print(IR_ONE_PIN);
  Serial.println(")...");
  
  // Note: Standard digital pins don't have a reliable software "fail state" 
  // like I2C or analog, but we maintain the boolean architecture!
  return true;
}

bool init_ir_two() {
  pinMode(IR_TWO_PIN, INPUT);
  Serial.print("Checking IR Sensor Two (Pin ");
  Serial.print(IR_TWO_PIN);
  Serial.println(")...");
  
  return true;
}

bool read_ir_one() {
  // Returns true if an obstacle is detected (signal goes LOW)
  return digitalRead(IR_ONE_PIN) == LOW;
}

bool read_ir_two() {
  // Returns true if an obstacle is detected (signal goes LOW)
  return digitalRead(IR_TWO_PIN) == LOW;
}

#endif