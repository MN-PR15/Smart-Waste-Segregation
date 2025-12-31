/*
 * Smart Waste Segregation System
 * Author: [Mohit nautiyal]
 * Date: 2025
 * * Description:
 * This system uses an Ultrasonic Sensor to detect presence and a 
 * Moisture Sensor to classify waste as Wet or Dry.
 * A Servo motor then directs the waste to the appropriate compartment.
 */

#include <Servo.h>

// --- COMPONENT CONFIGURATION ---
Servo sortingServo;  // Renamed from lidServo to be more descriptive

// Pin Definitions
const int TRIG_PIN  = 8;
const int ECHO_PIN  = 9;
const int SOIL_PIN  = A0;
const int SERVO_PIN = 7;

// Calibration Constants (Easy to tweak here)
const int DIST_THRESHOLD_CM = 20;     // Distance to trigger system
const int MOISTURE_THRESHOLD = 700;   // Below this = Wet
const int SERVO_NEUTRAL = 79;         // Resting position
const int SERVO_WET_POS = 145;        // Angle for Wet bin
const int SERVO_DRY_POS = 10;         // Angle for Dry bin

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  sortingServo.attach(SERVO_PIN);
  sortingServo.write(SERVO_NEUTRAL); 

  Serial.println(">> Smart Dustbin System Initialized...");
  Serial.println("------------------------------------");
}

void loop() {
  // 1. Measure Distance (Standard Ultrasonic Pulse)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // 2. Detection Logic
  if (distance > 0 && distance < DIST_THRESHOLD_CM) {
    Serial.print("Object Detected at: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    Serial.println("Analyzing waste content (3s)...");

    bool wetDetected = false;
    unsigned long startTime = millis();

    // 3. Analysis Phase (Non-blocking sampling)
    while (millis() - startTime < 3000) {
      int moistureValue = analogRead(SOIL_PIN);
      
      // Optional: Print only if significant change to reduce spam
      // Serial.println(moistureValue); 

      if (moistureValue < MOISTURE_THRESHOLD) {
        wetDetected = true;
        // Break early if we are sure it's wet? 
        // Or keep scanning to be sure? (Current logic keeps scanning, which is fine)
      }
      delay(100); // Small delay to stabilize reading
    }

    // 4. Actuation Phase
    Serial.println("--------------------------------");
    Serial.print("Result: ");

    if (wetDetected) {
      Serial.println("WET WASTE DETECTED");
      sortingServo.write(SERVO_WET_POS);
    } else {
      Serial.println("DRY WASTE DETECTED");
      sortingServo.write(SERVO_DRY_POS);
    }

    // 5. Reset Phase
    delay(5000); // Wait for waste to fall/slide
    sortingServo.write(SERVO_NEUTRAL); // Return to center
    Serial.println("System Reset. Ready for next.");
    Serial.println("--------------------------------");
  }
  
  delay(200); // Idle loop delay
}