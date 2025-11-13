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

struct dhParameters {
  float linkLength ;
  float linkTwist ; 
  float jointAngle ; 
  float linkOffset ;  
};

std::array<dhParameters, 6> dhTable {{
  {0, M_PI_2 , 40.0f , 0.0f}, //Link 1 
  {50.0f, M_PI , 40.0f , 0.0f}, //Link 2 
  {50.0f, M_PI , 40.0f , 0.0f}, //Link 3 
  {0, M_PI_2 , 50.0f, 0.0f}, //Link 4 
  {0, M_PI_2 , 0.0f , 0.0f}, //Link 5 
  {0, M_PI_2 , 50.0f , 0.0f}, //Link 6 

}};

void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(10);
  }

  run = true;
  Serial.printf("[MAIN] : C++ version macro: %ld\n", (long)__cplusplus);
  Serial.println("[MAIN] : Setup Done");
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
    Serial.printf("[UTILITY] : Time elapsed : %lld ms\n",
      static_cast<long long>(timeElapsed_ms.count()));
    Serial.println("[WATCHDOG] : Watchdog breach!");
    delay_mainCycle = 0ms;  
  }
}
