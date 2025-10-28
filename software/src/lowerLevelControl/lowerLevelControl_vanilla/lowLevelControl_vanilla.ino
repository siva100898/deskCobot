#include <SCServo.h>

// Create servo object
SMS_STS st;

// Servo configuration
#define SERVO_ID 1
#define BAUD_RATE 1000000

// Positions (0–4095 ticks)
const int POS_UP   = 4095;
const int POS_MID  = 2000;
const int POS_DOWN = 700;

// Motion parameters
const int SPEED_FAST = 2000; //>3000 = overcurrent stop 
const int SPEED_MED  = 1500;
const int ACCEL      = 50;

// Timing
const int DELAY_SHORT = 2000; // ms
const int DELAY_LONG  = 5000; // ms

void setup() {
    // Initialize Serial at the servo baud rate
    Serial.begin(BAUD_RATE, SERIAL_8N1);
    st.pSerial = &Serial;

    // Small startup delay
    delay(1000);
}

void loop() {
    // Move to UP position
    st.WritePosEx(SERVO_ID, POS_UP, SPEED_FAST, ACCEL);
    delay(DELAY_SHORT);

    // Move to MID position
    st.WritePosEx(SERVO_ID, POS_MID, SPEED_MED, ACCEL);
    delay(DELAY_SHORT);

    // Move to DOWN position
    st.WritePosEx(SERVO_ID, POS_DOWN, SPEED_MED, ACCEL);
    delay(DELAY_LONG);
}
