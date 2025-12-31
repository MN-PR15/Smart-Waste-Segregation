# 🗑️ Smart Waste Segregation System (IoT)

**Automated. Hygienic. Efficient.**

An IoT-based waste management solution designed to segregate Wet and Dry waste at the source using sensor fusion.

*([Click here to watch the Demo Video](https://drive.google.com/file/d/1iQUPsly6-zjRffiyjZVlNY-MLpxbe15I/view?usp=sharing))*

## 💡 The Problem
Improper waste disposal leads to landfills overflowing with mixed garbage, making recycling impossible. Manual segregation is hazardous and inefficient.

## ⚙️ How It Works
The system uses a **multi-sensor approach** to classify waste in real-time:
1.  **Detection:** An **Ultrasonic Sensor** detects a user approaching and automatically opens the lid (Touch-free interface).
2.  **Classification:** A **Moisture Sensor** analyzes the waste content.
    * *High Moisture:* Classified as **Wet Waste**.
    * *Low Moisture:* Classified as **Dry Waste**.
3.  **Sorting:** A **Servo Motor** rotates the internal chute to direct the waste into the correct compartment.

## 🛠️ Hardware Stack
* **Microcontroller:** Arduino Uno (ATmega328P)
* **Sensors:** * HC-SR04 Ultrasonic Sensor (Proximity)
    * Soil Moisture Sensor Module (Classification)
* **Actuators:** SG90 Servo Motors (Lid & Chute control)
* **Language:** C++ (Arduino IDE)

## 🔌 Circuit Logic
The system logic is written in **C++**. It continuously polls the sensor data loop. When the ultrasonic distance `< 20cm`, it triggers the interrupt to open the lid. Upon waste deposit, the moisture threshold determines the angle of the sorting servo ($0^\circ$ for Dry, $180^\circ$ for Wet).

---
*Built by [Mohit Nautiyal]*
