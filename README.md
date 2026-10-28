# DristiGati — Autonomy Beyond the Map

**A vision-based disaster reconnaissance rover prototype | Hack in Hills 2026**

> Helping rescue teams search difficult environments through robotic sensing, computer vision, and human-supervised decisions.

## About the Project

DristiGati is a disaster-reconnaissance robot prototype designed around a problem that emerges after earthquakes, building collapses, and other disasters: locating potential survivors in environments that may be unstable, obstructed, or unfamiliar.

The project explores how a mobile rover can combine obstacle detection, person detection, and a monitoring dashboard to support reconnaissance. Rather than treating every AI detection as an unquestionable command, DristiGati incorporates a **human-in-the-loop workflow**, allowing an operator to review a detection and approve the next step.

Our goal is to support rescue teams by helping them gather information from difficult-to-access areas—not to replace human rescuers or emergency-response professionals.

## Key Features

- **Person detection:** A computer-vision pipeline using YOLO and OpenCV to identify people in camera footage.
- **Obstacle-aware movement:** Ultrasonic distance sensing to help the rover detect nearby obstacles and make movement decisions.
- **Servo-assisted scanning:** A servo-mounted distance sensor can scan different directions to help evaluate available clearance.
- **Operator dashboard:** A software interface for monitoring the system and reviewing detection status.
- **Human-in-the-loop control:** The operator reviews a detection and confirms whether the system should continue.
- **Hardware simulation and testing:** Hardware-related files are included to support circuit inspection and development.

## How It Works

The intended workflow connects sensing, AI-assisted detection, and operator supervision.

```text
        ENVIRONMENT
             |
             v
     Rover Sensing
             |
       +-----+------+
       |            |
       v            v
 Obstacle Scan   Camera Input
       |            |
       |            v
       |      Person Detection
       |            |
       +-----+------+
             |
             v
      System Status
             |
             v
      Operator Review
             |
        Human Approval
             |
             v
   Continue / Next Action
```

The precise level of integration depends on the hardware and software components running in a given test. The diagram describes the intended system workflow, not a claim that every stage is fully autonomous or deployed on the rover.

## Hardware

The rover prototype is built around an ESP32-based control system and supporting motor-control and sensing components.

| Component | Purpose |
|---|---|
| ESP32 DevKit | Main microcontroller for rover control |
| Four-wheel-drive chassis and DC motors | Mobile rover platform |
| Motor driver boards | Control motor direction and movement |
| PCA9685 PWM driver | Generate control signals for connected motors and the servo |
| HC-SR04 ultrasonic sensor | Measure distance to nearby obstacles |
| SG90 servo motor | Change the sensor's scanning direction |
| Battery and voltage regulation | Supply power to the electronics and motors |

The hardware configuration may evolve during testing. Consult the circuit files in `Hardware/` for the wiring and component arrangement used in the corresponding build.

## Software

The software side combines a dashboard, a computer-vision pipeline, and control logic.

- **Python:** Computer-vision and backend development.
- **YOLO and OpenCV:** Person detection and camera-frame processing.
- **Flask:** Backend API and communication between connected software components.
- **React and Vite:** Frontend dashboard development.
- **Arduino framework / ESP32:** Embedded rover-control firmware.
- **PCA9685 and ultrasonic sensing:** Motor-control signals and distance measurements.

The camera-based person-detection pipeline and the rover's obstacle-avoidance logic are distinct functions. Their integration should be tested rather than assumed from the presence of individual components.

## Repository Structure

```text
DristiGati-Round-2/
├── Hardware/
│   └── DristiGati Hardware Circuit Diagram.png
│   └── How to use Hardware Simulation.md
│   └── Sketch.ino
│   └── diagram.json
│   └── libraries.txt
├── DristiGati-Frontend.zip
└── README.md
```

The `Hardware/` directory contains the hardware-related resources for the prototype. `Frontend.zip` contains the frontend project as an archive. `Backend.zip` contains the backend related files as an archive.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/upadhritisingh/DristiGati-Round-2.git
cd DristiGati-Round-2
```

### 2. Explore the hardware resources

Open `Hardware/` and review the available circuit diagrams, firmware, and simulation instructions before trying out the simulation yourself.


### 3. Extract the frontend

Extract `Frontend.zip` and `Backend.zip` into a separate folder. Open that folder in VS Code and inspect its `package.json` for the project's available scripts.

```bash
npm install
npm run dev
```

Run these commands from the extracted frontend directory, provided the corresponding scripts are present in `package.json`.

### 4. Configure connected components

Follow the setup instructions supplied with the backend and firmware versions you intend to use. Confirm that API addresses, camera access, serial communication, and hardware pin assignments match your current configuration before testing the complete workflow.

## Current Scope and Limitations

DristiGati is a developing prototype. Its current scope is focused on exploring the integration of a mobile rover, obstacle sensing, person detection, and operator-supervised decisions.

- Person detection does not establish that a detected person is injured or trapped.
- Ultrasonic sensing provides limited distance information; it does not create a complete map of the environment or reliably identify every hazard.
- A successful software simulation does not by itself demonstrate reliable operation in real disaster conditions.
- Autonomous navigation, robust mapping, field-tested reliability, and real-world rescue deployment should not be considered completed capabilities unless independently implemented and tested.

These limitations are important because a disaster-response system must be evaluated for safety and reliability before it can be used operationally.

## Future Scope

Potential development directions include:

- More robust integration between the camera pipeline, rover firmware, and dashboard.
- Improved obstacle handling and safer movement decisions.
- Better detection-status notifications and operator controls.
- Mapping and localization capabilities for unfamiliar environments.
- Expanded testing across simulated and physical environments.
- Reliability and fail-safe testing before any real-world deployment.

## Why DristiGati?

The name draws on *Dristi*—vision or sight—and reflects the project's emphasis on perception and awareness.

**Autonomy Beyond the Map** expresses our ambition to explore how robots can gather useful information in unfamiliar environments, while keeping human judgment central to critical decisions.

DristiGati is built to support rescue teams—not replace them.

---

**Built for Hack in Hills 2026**  
**Project:** DristiGati — Autonomy Beyond the Map
**Team:** TriLogic
