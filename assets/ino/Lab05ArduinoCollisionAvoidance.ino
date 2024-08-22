// Lab05ArduinoCollisionAvoidance.ino
//
// Collision Avoidance System
//
// Author: Steve Ellermann
// 
// Created:  2023-03-24
// Modified: 2023-04-01
//
// Libraries Required:
// Stepper.zip
// HC-SR04.zip
// pitches.zip
// Servo.zip
//
//  Wiring:
// -------------------------------------------------
// Pin Digital GND | Breadboard 5V
// Pin 13          | Echo - Ultrasonic Sensor
// Pin 12          | Trig - Ultrasonic Sensor
// Pin 11          | IN1 - ULN2003 Driver Board
// Pin 10          | IN2 - ULN2003 Driver Board
// Pin  9          | IN3 - ULN2003 Driver Board
// Pin  8          | IN4 - ULN2003 Driver Board
// Pin  7          | + on Passive Buzzer
// Pin  6          | Orange Wire - SG90 Servo Motor
// Power GND       | GND - Ultrasonic Sensor
// Power 5V        | Breadboard 5V
// -------------------------------------------------
//
// Supplies
//
// Software:
// (1) x Arduino IDE (ver 2 was used)
//
// Hardware:
// (1) x Elegoo UNO R3
// (1) x SG90 Servo Motor
// (1) x HC-SR04 Ultrasonic Sensor Module
// (1) x MB-V2 Breadboard Power Supply Module
// (1) x 5V Passive Buzzer
// (1) x 28BYJ-48 5V Stepper Motor
// (1) x 830 tie-points breadboard
// (1) x 9V 1A Battery Adapter
// (1) x 9V Battery
// (8) x F-M wires (Female to Male DuPont wires)
// (8) x M-M wire (Male to Male jumper wire)
// (1) x USB 2.0 Type A to USB 2.0 Type B Cable
// (Optional) (1) x USB-C to USB Adapter
//

// Libraries
// #include "Stepper.h"         // library for stepper motor
#include "AccelStepper.h"    // library for stepper motor
#include "SR04.h"            // library for ultrasonic sensor
#include "pitches.h"         // library for passive buzzer
#include "Servo.h"           // library for servo motor

// Definitions
#define SERVO_PIN 6          // Pin for servo motor
#define BUZZER_PIN 7         // Pin for passive buzzer
#define STEPPER_PIN_1 8      // Pin for stepper motor
#define STEPPER_PIN_2 9      // Pin for stepper motor
#define STEPPER_PIN_3 10     // Pin for stepper motor
#define STEPPER_PIN_4 11     // Pin for stepper motor
#define ECHO_PIN 12          // Pin for ultrasonic sensor
#define TRIG_PIN 13          // Pin for ultrasonic sensor
#define STEPPER_STEPS 32     // Number of steps per revolution of stepper motor internal shaft
#define MotorInterfaceType 8 // Define the AccelStepper interface type; 4 wire motor in half step mode:

// Constants
const int STEPPER_STEPS_TO_TAKE = 30;               // 2048 = 1 Revolution of stepper motor
// const int STEPPER_SPEED = 500;                      // Stepper motor speed max seems to be 500
const int STEPPER_SPEED = 500;                      // Stepper motor speed
const int STEPPER_MAX_SPEED = 1000;                 // Stepper motor speed max speed
const int THRESHOLD = 5;                            // Threshold distance in cm
const bool DEBUG = false;                           // Display debug information

// Variables
int servoPosition = 0;                              // variable to store the servo position
unsigned long ultrasonicDistance;                   // initialize ultrasonic sensor variable for distance
unsigned int toggleStepperRotation = 0;             // toggle stepper rotation
bool hasRunOnce = 0;                                // has the program run once


// Objects

// Instantiate the stepper library
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4 for the 28BYJ-48 stepper motor
//Stepper myStepper(STEPPER_STEPS, STEPPER_PIN_0, STEPPER_PIN_2, STEPPER_PIN_1, STEPPER_PIN_3);

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor:
AccelStepper  myStepper = AccelStepper(MotorInterfaceType, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);

// Instantiate servo object to control a servo
Servo myServo;  

// Instantiate the ultrasonic sensor
SR04 myUltrasonic = SR04(ECHO_PIN,TRIG_PIN);

// Run once
void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);                        // attaches the servo on SERVO_PIN to the servo object
  
  // Set the maximum steps per second:
   myStepper.setMaxSpeed(STEPPER_MAX_SPEED);
}

// Run repeatedly
void loop() {

  if (hasRunOnce == 0) {
    
    if (DEBUG) {                                                         // print information for debugging
      Serial.println("hasRunOnce: No");                                  // print if program has run once
      Serial.println("Stepper Motor Rotation: clockwise");               // print stepper motor rotation direction
    }
    
    hasRunOnce = 1;                                                   // update the variable
    
    stepperRotateClockwise();                                            // rotate stepper motor clockwise
    
  } else {
   
    ultrasonicDistance = myUltrasonic.Distance();                        // update ultrasonic sensor variable
    
    if (DEBUG) {                                                         // print information for debugging
      Serial.print("Ultrasonic Sensor Distance: ");                      // print the distance from the ultrasonic sensor in cm
      Serial.print(ultrasonicDistance);                                  // print the distance from the ultrasonic sensor in cm
      Serial.println(" cm");                                             // print the distance from the ultrasonic sensor in cm
    }
    
    if (ultrasonicDistance <= THRESHOLD) {                               // toggle the variable based on distance from ultrasonic sensor
    
      toggleStepperRotation = 1;

    } else {

      toggleStepperRotation = 0;

    }
    
    /*
    switch(toggleStepperRotation) {                                      // decision loop
      
      case 0:
        if (DEBUG) { 
          Serial.println("Stepper Motor Rotation: clockwise");             // print stepper motor rotation direction
        }
        muteBuzzer();
        servoRotateToZero();
        stepperRotateClockwise();
        break;
        
      case 1:
        if (DEBUG) {       
          Serial.println("Stepper Motor Rotation: counterclockwise");      // print stepper motor rotation direction
        }
        playBuzzer();
        servoRotateToOneEighy();
        stepperRotateCounterClockwise();
        break;
        
      default:
        break;
    }
    */
    
  }

}

// Rotate stepper motor clockwise
void stepperRotateClockwise() {
  myStepper.setSpeed(STEPPER_SPEED);                                     // stepper motor speed
  //myStepper.step(STEPPER_STEPS_TO_TAKE);                                 // rotate clockwise
  myStepper.runSpeed();                                                  // rotate clockwise
}

// Rotate stepper motor counter clockwise
void stepperRotateCounterClockwise() {
  myStepper.setSpeed(-STEPPER_SPEED);                                     // stepper motor speed
  //myStepper.step(-STEPPER_STEPS_TO_TAKE);                                // rotate counterclockwise
  myStepper.runSpeed();                                                  // rotate clockwise
}

// Play a tone
void playBuzzer() {
  tone(BUZZER_PIN, NOTE_G5, 100);                                        // play a tone on the passive buzzer
}

// Mute the tone
void muteBuzzer() {
  noTone(BUZZER_PIN);                                                    // turn the tone off
}

// Rotate servo motor to 0 degrees
void servoRotateToZero() {                                               // rotate servo to 0 degree position
  for (servoPosition = 180; servoPosition >= 0; servoPosition -= 1) {    // goes from 180 degrees to 0 degrees in steps of 1 degree
    myServo.write(servoPosition);                                        // tell servo to go to position in variable 'pos'
  }
}

// Rotate servo motor to 180 degrees
void servoRotateToOneEighy() {                                           // rotate servo to 180 degree position
  for (servoPosition = 0; servoPosition <= 180; servoPosition += 1) {    // goes from 0 degrees to 180 degrees in steps of 1 degree
    myServo.write(servoPosition);                                        // tell servo to go to position in variable 'servoPosition'
  }  
}
