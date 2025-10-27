#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32 Serial test OK");
}

void loop() {
  Serial.println("Hello every 2 seconds");
  delay(2000);
}
