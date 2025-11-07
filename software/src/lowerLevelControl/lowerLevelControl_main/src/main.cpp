#include <Arduino.h>
#include <array>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <optional>
#include <chrono>
#include <esp_timer.h>

using namespace std::chrono;

bool run;
int counter;
auto delay_mainCycle = 0ms;

steady_clock::time_point lastCycle;
constexpr auto watchDogThreshold = 50ms;

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(10);
  }

  run = true;
  Serial.printf("C++ version macro: %ld\n", (long)__cplusplus);
  Serial.println("Setup is running!");
}

void loop() {
  auto startCycle = steady_clock::now();

  // -------- Main section --------
  counter = 0;
  while (counter < 50) {
    counter = counter + 1;
  }

  delay(delay_mainCycle.count());  // convert chrono::duration to integer milliseconds
  delay_mainCycle += 1ms;

  auto endCycle = steady_clock::now();
  auto timeElapsed = endCycle - startCycle;
  auto timeElapsed_ms = duration_cast<milliseconds>(timeElapsed);

  

  if (timeElapsed > watchDogThreshold) {
    Serial.printf("[UTILITY] Time elapsed : %lld ms\n",
      static_cast<long long>(timeElapsed_ms.count()));
    Serial.println("[WATCHDOG] Watchdog breach!");
    delay_mainCycle = 0ms;  // ✅ properly resets
  }
}
