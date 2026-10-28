# 🤖 DristiGati: Autonomous Disaster Rescue Rover

SIMULATION LINK: https://wokwi.com/projects/479135462706510849

An intelligent, 4-wheel drive autonomous reconnaissance rover engineered to navigate hazardous disaster zones, autonomously dodge obstacles and drop-offs, and stream real-time visual telemetry to an AI-powered React dashboard for survivor rescue operations.

---

## 🚀 Key Autonomous Features & Navigation Logic

### 1. Precision 4-Wheel Drive (4WD) Kinematics
* Utilizes a dual-TB6612FNG motor driver configuration governed by an I2C PCA9685 PWM controller, enabling smooth arc-pivoting and responsive rotational maneuvers.

### 2. Intelligent Obstacle Avoidance (< 15 cm Threshold)
* **The Scan:** When the front-facing ultrasonic sensor detects an obstacle closer than **15 cm**, the rover halts.
* **Surrounding Assessment:** A pan-servo sweeps the sensor left (160°) and right (20°) to evaluate alternative paths.
* **Path Selection:** The system compares clearance metrics and pivots in an arc toward the safer route.
* **Tie-Breaker Rule:** If both paths are equal, the rover executes a controlled slow right turn to explore safely.

### 3. Precision Cliff Avoidance (> 15 cm Threshold)
* Powered by a downward-facing VL53L0X Time-of-Flight (ToF) laser sensor. If the floor distance drops past **15 cm** (simulating a chasm or edge), the rover instantly reverses and pivots away to prevent a catastrophic fall.

### 4. Interactive Judge Test Panel (Wokwi Simulation)
We integrated interactive push buttons directly into the Wokwi schematic so judges can test edge cases instantly:
* 🔴 **Red Button ("Cliff"):** Triggers the cliff-avoidance retreat and reverse-arc sequence.
* 🟢 **Green Button ("Left Obs"):** Simulates a close obstacle on the left, forcing a right-pivot escape.
* 🔵 **Blue Button ("Right Obs"):** Simulates a close obstacle on the right, forcing a left-pivot escape.
* 🎚️ **Front Sensor Slider:** Drag the HC-SR04 distance slider below 15 cm to test automated scanning live.

---

## 🛠️ DristiGati Hardware Architecture

```text
 ┌───────────────────────────┐         Wi-Fi Stream          ┌──────────────────────────────┐
 │     ESP32 Microcontroller │ ────────────────────────────> │  React / Vite Dashboard      │
 │  • PCA9685 PWM Driver     │                               │  • Live MJPEG Video Stream   │
 │  • TB6612FNG 4WD Motors   │         Bounding Boxes        │  • YOLO Person Detection     │
 │  • I2C Cliff & Ultrasonic │ <──────────────────────────── │    (Survivor Identification) │
 └───────────────────────────┘                               └──────────────────────────────┘
