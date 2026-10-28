#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// --- Pin Definitions ---
const int frontTrigPin = 23;
const int frontEchoPin = 4;   
const int servoPin = 13;

// Interactive Judge Push Buttons
const int cliffBtnPin = 33;   // Red Button (Cliff)
const int leftObsBtnPin = 15; // Green Button (Left Obstacle)
const int rightObsBtnPin = 32;// Blue Button (Right Obstacle)

// Motor Driver Pins (4-Wheel Drive Groups)
const int leftMotorForward = 25;
const int leftMotorBackward = 26;
const int rightMotorForward = 27;
const int rightMotorBackward = 14;

Servo scannerServo;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
bool loxInitialized = false;
bool wasMovingForward = false; // Tracks robot state for clean logging

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA = 21, SCL = 22

  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);

  pinMode(cliffBtnPin, INPUT_PULLUP);
  pinMode(leftObsBtnPin, INPUT_PULLUP);
  pinMode(rightObsBtnPin, INPUT_PULLUP);

  if (!lox.begin()) {
    loxInitialized = false; 
  } else {
    loxInitialized = true;
  }

  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  scannerServo.attach(servoPin);
  scannerServo.write(90); // Center position

  stopRobot();
  Serial.println("Disaster Rover Online. Moving Forward...");
  wasMovingForward = true;
}

void loop() {
  // 1. Check Interactive Buttons (Manual Demo Overrides)
  bool cliffButtonPressed = (digitalRead(cliffBtnPin) == LOW);
  bool leftObsTriggered = (digitalRead(leftObsBtnPin) == LOW);
  bool rightObsTriggered = (digitalRead(rightObsBtnPin) == LOW);

  if (cliffButtonPressed) {
    wasMovingForward = false;
    Serial.println("👉 [DEMO] Cliff button pressed! Reversing & pivoting away...");
    moveBackward();
    delay(800);
    pivotRightArc(); 
    delay(600);
    return;
  }

  if (leftObsTriggered) {
    wasMovingForward = false;
    Serial.println("👉 [DEMO] Left Obstacle triggered! Pivoting Right...");
    stopRobot();
    scannerServo.write(160); 
    delay(400);
    scannerServo.write(90);
    pivotRightArc();
    delay(800);
    return;
  }

  if (rightObsTriggered) {
    wasMovingForward = false;
    Serial.println("👉 [DEMO] Right Obstacle triggered! Pivoting Left...");
    stopRobot();
    scannerServo.write(20); 
    delay(400);
    scannerServo.write(90);
    pivotLeftArc();
    delay(800);
    return;
  }

  // 2. Automated Cliff Check
  long floorDistance = 5; 
  if (loxInitialized) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    if (measure.RangeStatus != 4) {
      floorDistance = measure.RangeMilliMeter / 10; 
    }
  }

  if (floorDistance > 15) {
    wasMovingForward = false;
    Serial.println("⚠️ CLIFF DETECTED! Reversing and pivoting away...");
    moveBackward();
    delay(800);
    pivotRightArc(); 
    delay(600);
    return;
  }

  // 3. Check Front Obstacle Sensor (Slider)
  long frontDistance = getFrontDistance();

  if (frontDistance > 0 && frontDistance < 15) {
    wasMovingForward = false;
    Serial.print("🛑 Obstacle at ");
    Serial.print(frontDistance);
    Serial.println(" cm! Scanning surroundings...");
    
    stopRobot();
    
    // Scan Left
    scannerServo.write(160);
    delay(500);
    long leftDistance = getFrontDistance();
    
    // Scan Right
    scannerServo.write(20);
    delay(700);
    long rightDistance = getFrontDistance();
    
    // Center Servo back
    scannerServo.write(90);
    delay(400);

    Serial.print("   -> Left Path: "); Serial.print(leftDistance);
    Serial.print(" cm | Right Path: "); Serial.print(rightDistance); Serial.println(" cm");

    if (leftDistance > rightDistance) {
      Serial.println("   -> Left path clearer. Pivoting Left.");
      pivotLeftArc();
      delay(700);
    } 
    else if (rightDistance > leftDistance) {
      Serial.println("   -> Right path clearer. Pivoting Right.");
      pivotRightArc();
      delay(700);
    } 
    else {
      Serial.println("   -> Equal paths. Turning right slowly to search...");
      turnRightSlow();
      delay(800);
    }
  } else {
    // Path is clear! Print message once when transitioning back to moving forward
    if (!wasMovingForward) {
      Serial.println("🟢 Path clear. Resuming forward movement...");
      wasMovingForward = true;
    }
    moveForward(); 
  }
  
  delay(100);
}

long getFrontDistance() {
  digitalWordWrite: // (just standard logic)
  digitalWrite(frontTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrigPin, LOW);
  
  long duration = pulseIn(frontEchoPin, HIGH, 30000);
  if (duration == 0) return 99; 
  return (duration * 0.034 / 2);
}

void moveForward() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

void pivotLeftArc() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

void pivotRightArc() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

void turnRightSlow() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void stopRobot() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}