#include <Arduino.h>

// Servo pin & channel
#define SERVO_PIN      2
#define SERVO_CHANNEL  0

// PWM config (ESP32 ledc, 50 Hz, 16-bit resolution)
const int PWM_RES_BITS = 16;
const int DUTY_MIN     = 1638;   // ≈0.5 ms pulse (0°)
const int DUTY_MAX     = 8192;   // ≈2.5 ms pulse (180°)

// Convert angle (0–180) to duty cycle
inline int angleToDuty(int angle) {
  angle = constrain(angle, 0, 180);
  return map(angle, 0, 180, DUTY_MIN, DUTY_MAX);
}

void setup() {
  Serial.begin(115100);

  // Setup PWM channel
  ledcSetup(SERVO_CHANNEL, 50, PWM_RES_BITS);
  ledcAttachPin(SERVO_PIN, SERVO_CHANNEL);

  // Move servo to 0°
  ledcWrite(SERVO_CHANNEL, angleToDuty(90));
  Serial.println("Servo on pin 2 moved to 0°");
}

void loop() {
  // Nothing here — servo stays at 0°
}
