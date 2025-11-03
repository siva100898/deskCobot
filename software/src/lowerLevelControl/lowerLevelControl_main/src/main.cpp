#include <Arduino.h>

bool run ; 
void setup() {
    Serial.begin(115200);

    // Wait for Serial to be ready (especially for ESP32)
    while (!Serial) {
        delay(10);
    }
    run = true ; 
    Serial.println("Setup is running!");
}

void loop() {
  if (run){
    Serial.println("Loop is running...");
    run = false ; 
  }
  delay(1000);
}
