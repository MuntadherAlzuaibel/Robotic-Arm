#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> // Include the Adafruit PWM Servo Driver library

Adafruit_PWMServoDriver Driver = Adafruit_PWMServoDriver(0x40);

#define SDA_PIN 21
#define SCL_PIN 22

#define base_channel 0
#define Rshoulder_channel 1
#define Lshoulder_channel 2
#define elbow_channel 3
#define wrist_channel 4
#define claw_channel 5

#define minUs 750 // Servo pulse width range
#define maxUs 2250 // Servo pulse width range

int angleToUs(int angle) // Convert angle (0–180) to pulse width in microseconds (for 50 Hz servo signal)
{
  // Ensure angle is within valid range to eliminate jitter
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  return map(angle, 0, 180, minUs, maxUs); // Map angle to pulse width
}

void sendPWM(int channel, int angle)
{
  Driver.writeMicroseconds(channel, angleToUs(angle)); // Write duty cycle to servo channel
}

void setShoulder(int angle)
{
  sendPWM(Rshoulder_channel, angle);
  sendPWM(Lshoulder_channel, 180 - angle); // Invert left shoulder movement
}

void setup() 
{
  Serial.begin(115200); // Initialize serial communication
  Serial.println("Robotic Arm Initialized");

  /////////////////// Servo Driver Setup (PCA9685) /////////////////////

  Wire.begin(SDA_PIN, SCL_PIN); // Initialize I2C
  Driver.begin(); // Initialize the PCA9685
  Wire.setClock(100000);   // keep it slow (100 kHz) while debugging
  Driver.setPWMFreq(50); // Set frequency to 50 Hz for servos

  // Move servos to initial Parking positions
  //sendPWM(base_channel, 90); delay(100);   
  //setShoulder(0); delay(100);
  //sendPWM(elbow_channel, 180); delay(100);
  //sendPWM(wrist_channel, 40); delay(100);
  //sendPWM(claw_channel, 150); delay(100);
  delay(300);
}

// Global variables to store current angles
int baseAngle = 90; // Default base angle
int shoulderAngle = 0; // Default shoulder angle
int elbowAngle = 180; // Default elbow angle
int wristAngle = 40; // Default wrist angle
int clawAngle = 90; // Default claw angle

void loop()
{ 
  if (Serial.available()) 
  {
    Serial.print("Robot ready");
    char command = Serial.read(); 
    Serial.println(command);

    if (command == '\n' || command == '\r') return; // ignore line endings

    switch (command) 
    {
      case 'w':
        setShoulder(shoulderAngle += 5);
        Serial.println("Shoulder moved to " + String(shoulderAngle) + "°");
        break;

      case 's':
        setShoulder(shoulderAngle -= 5);
        Serial.println("Shoulder moved to " + String(shoulderAngle) + "°");
        break;

      case 'a':
        sendPWM(base_channel, baseAngle -= 5);
        Serial.println("Base rotated to " + String(baseAngle) + "°");
        break;

      case 'd':
        sendPWM(base_channel, baseAngle += 5);
        Serial.println("Base rotated to " + String(baseAngle) + "°");
        break;

      case 'q':
        sendPWM(elbow_channel, elbowAngle -= 5);
        Serial.println("Elbow moved to " + String(elbowAngle) + "°");
        break;

      case 'e':
        sendPWM(elbow_channel, elbowAngle += 5);
        Serial.println("Elbow moved to " + String(elbowAngle) + "°");
        break;
      
      case 'z':
        sendPWM(wrist_channel, wristAngle += 5);
        Serial.println("Wrist moved to " + String(wristAngle) + "°");
        break;
      
      case 'c':
        sendPWM(wrist_channel, wristAngle -= 5);
        Serial.println("Wrist moved to " + String(wristAngle) + "°");
        break;
      
      case 'r':
        sendPWM(claw_channel, clawAngle += 5);
        Serial.println("Claw moved to " + String(clawAngle) + "°");
        break;

      case 'f':
        sendPWM(claw_channel, clawAngle -= 5);  
        Serial.println("Claw moved to " + String(clawAngle) + "°");
        break;
        
      default:
        Serial.println("Invalid command. Use '0' to '4' to move the shoulder.");
        break;
    }
  }
}
