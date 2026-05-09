# Arduino-Based Smart Car Parking System

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![Language](https://img.shields.io/badge/Language-C++-orange)
![Status](https://img.shields.io/badge/Project-Completed-brightgreen)

---

## Overview

An embedded systems project that demonstrates real-time parking slot monitoring using Arduino UNO and HC-SR04 ultrasonic sensor technology. The system automatically detects vehicle presence and updates parking slot occupancy status based on measured distance.

---

## Features

- Real-time vehicle detection
- Automated parking slot monitoring
- Distance measurement using ultrasonic sensing
- Serial monitor status updates
- Low-cost embedded system implementation
- Beginner-friendly modular design

---

## Tech Stack

- Arduino UNO
- Embedded C / Arduino IDE
- HC-SR04 Ultrasonic Sensor

---

## Hardware Components

| Component | Quantity |
|-----------|----------|
| Arduino UNO | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| Breadboard | 1 |
| Jumper Wires | Multiple |
| Servo Motor (Optional) | 1 |

---

## Working Principle

The HC-SR04 ultrasonic sensor continuously transmits ultrasonic waves and receives reflected echo signals from nearby objects.

Arduino UNO calculates the distance using the echo pulse duration.

If the measured distance is less than the predefined threshold value, the system detects a vehicle and marks the parking slot as occupied. Otherwise, the parking slot is considered available.

---

## System Workflow

1. Ultrasonic sensor sends ultrasonic pulse
2. Echo signal is received
3. Arduino calculates distance
4. Vehicle presence is detected
5. Parking slot status is updated

---

## Circuit Connections

| HC-SR04 Pin | Arduino UNO Pin |
|-------------|-----------------|
| VCC | 5V |
| GND | GND |
| TRIG | D9 |
| ECHO | D10 |

---

## System Architecture

![System Architecture](images/system_architecture.png)

---

## Circuit Diagram

![Circuit Diagram](images/circuit_diagram.png)

---

## Project Preview

### Hardware Setup
![Hardware Setup](images/hardware_setup.jpg)

### Prototype
![Prototype](images/prototype.jpg)

### Serial Monitor Output
![Serial Monitor](images/serial_monitor_output.png)

---

## Source Code

```c
#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
float distance;

const int thresholdDistance = 15;

void setup() {

    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.println("SMART CAR PARKING SYSTEM");
}

void loop() {

    distance = measureDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if(distance < thresholdDistance) {
        Serial.println("STATUS: SLOT OCCUPIED");
    }
    else {
        Serial.println("STATUS: SLOT AVAILABLE");
    }

    delay(1000);
}

float measureDistance() {

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    return duration * 0.034 / 2;
}
```

---

## Installation

1. Clone the repository
2. Open Arduino IDE
3. Connect Arduino UNO
4. Upload `smart_car_parking_system.ino`
5. Open Serial Monitor at 9600 baud rate
6. Test vehicle detection using the ultrasonic sensor

---

## Output

- Detects vehicle presence
- Displays parking slot status
- Updates occupancy information in real time

---

## Performance Metrics

| Parameter | Value |
|-----------|-------|
| Detection Accuracy | ~95% |
| Response Time | <1 second |
| Detection Range | 2cm – 400cm |
| Operating Voltage | 5V |

---

## Applications

- Smart parking systems
- Vehicle monitoring systems
- IoT-based parking solutions
- Smart city infrastructure

---

## Skills Demonstrated

- Embedded Systems
- Arduino Programming
- Sensor Interfacing
- Real-Time Monitoring
- Hardware Prototyping
- Circuit Design
- IoT Fundamentals

---

## Learning Outcomes

- Learned ultrasonic sensor interfacing
- Implemented real-time distance measurement
- Improved embedded systems debugging skills
- Understood hardware-software integration

---

## Future Enhancements

- IoT dashboard integration
- Mobile application support
- RFID authentication
- Multi-slot parking management
- Cloud database connectivity
- LCD/OLED display integration

---

## Repository Structure

```bash
arduino-smart-car-parking/
├── code/
├── diagrams/
├── docs/
├── images/
├── results/
├── LICENSE
└── README.md
```

---

## Author
Kavya R 

---

## License

This project is licensed under the MIT License.
