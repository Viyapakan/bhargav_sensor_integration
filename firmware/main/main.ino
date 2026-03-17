// Built-in LED is usually on GPIO 2 for these ESP32 boards
#define LED_PIN 2

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("ESP32 is alive! Starting Blink Test...");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn LED ON
  Serial.println("LED ON");
  delay(1000);                  // Wait 1 second
  
  digitalWrite(LED_PIN, LOW);   // Turn LED OFF
  Serial.println("LED OFF");
  delay(1000);                  // Wait 1 second
}