#define FLAME_SENSOR A0    // Analog input for flame sensor
#define BLUE_LED 2         // Blue LED indicator
#define GREEN_LED 3        // Green LED indicator
#define SERVO_PIN 9        // PWM pin for servo motor
#define BUZZER_PIN 10      // Buzzer for alarm

// Threshold values
#define FLAME_THRESHOLD 500 // Adjust based on your sensor's readings

// Servo positions
#define SERVO_OFF_POS 0    // Servo position when off
#define SERVO_ON_POS 90    // Servo position when activated

// Variables
int flameValue = 0;        // Store flame sensor reading
bool fireDetected = false; // Fire detection flag

// Include Servo library
#include <Servo.h>
Servo fireServo;           // Create servo object

void setup() {
  // Initialize pins
  pinMode(FLAME_SENSOR, INPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Attach servo to pin
  fireServo.attach(SERVO_PIN);
  fireServo.write(SERVO_OFF_POS); // Start with servo off
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initial status (no fire)
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  noTone(BUZZER_PIN);
  
  Serial.println("Fire Fighting Alarm System Initialized");
}

void loop() {
  // Read flame sensor value
  flameValue = analogRead(FLAME_SENSOR);
  
  // Print sensor value for debugging
  Serial.print("Flame Sensor Value: ");
  Serial.println(flameValue);
  
  // Check for fire
  if (flameValue < FLAME_THRESHOLD) {
    // Fire detected
    if (!fireDetected) {
      fireDetected = true;
      activateAlarm();
      Serial.println("Fire Detected! Alarm Activated");
    }
  } else {
    // No fire detected
    if (fireDetected) {
      fireDetected = false;
      deactivateAlarm();
      Serial.println("Fire Extinguished. System Normal");
    }
  }
  
  // Small delay to stabilize readings
  delay(200);
}

void activateAlarm() {
  // Turn on red LED and turn off green LED
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  
  // Activate servo (simulating fire fighting mechanism)
  fireServo.write(SERVO_ON_POS);
  
  // Sound the alarm buzzer
  tone(BUZZER_PIN, 1000); // 1kHz tone
}

void deactivateAlarm() {
  // Turn off red LED and turn on green LED
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  
  // Deactivate servo
  fireServo.write(SERVO_OFF_POS);
  
  // Turn off buzzer
  noTone(BUZZER_PIN);
}