// Lab04Arduino.ino
// -----------------------------------
// Author: Steve Ellermann
// Created: 2023-03-21
// Modified: 2023-03-22
// -----------------------------------
// This program drives a unipolar or bipolar stepper motor.
// The motor is attached to digital pins 8 - 11 of the Arduino.
//
// The stepper motor should revolve clockwise for 10 seconds, then stepper
// motor should revolve counterclockwise for 10 seconds.
// -----------------------------------
// Library Required: Stepper.zip
// https://github.com/arduino-libraries/Stepper
// -----------------------------------
// Components Used:
// -----------------------------------
// Arduino UNO R3 or Elegoo UNO R3
// 28BYJ-48 Stepper Motor
// 4 Phase ULN2003A Stepper Motor Driver PCB
// MB-V2 Breadboard Power Supply Module
// 830 Tie Point Solderless Plug-In Breadboard
// 9V Battery
// 9V Battery Snap-On Connector Clip
// USB A to USB B connector Cable
// (6) x F-M wires (Female to Male DuPont wires)
// (1) x M-M wire (Male to Male jumper wire)
// (1) x wire twist tie
//
// -----------------------------------
// Wiring
// -----------------------------------
// Stepper Motor Driver PCB INT1 to 11
// Stepper Motor Driver PCB INT2 to 10
// Stepper Motor Driver PCB INT3 to 9
// Stepper Motor Driver PCB INT4 to 8
// Stepper Motor Driver PCB - to Breadboard -5V 
// Stepper Motor Driver PCB + to Breadboard +5V
// Stepper Motor Driver PCB: Stepper moto plugs into stepper motor driver PCB
// Arduino UNO R3 or Elegoo UNO R3 Power GND to Breadboard -3.3V
//
// -----------------------------------

// libraries
#include <Stepper.h>

// constants won't change.
const int stepsPerRevolution = 2048;   // change this to fit the number of steps per revolution
const int revolutionsPerMinute = 6;    // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const long interval = 10000;           // interval at which to rotate (milliseconds)

// variables will change:
unsigned long previousMillis = 0;      // will store last time stepper motor was updated
unsigned long rotationDirection = 0;   // Initialize rotation direction to zero

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // set the stepper motor speed
  myStepper.setSpeed(revolutionsPerMinute);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  
  // will store the number of milliseconds passed since the program begain running
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you changed rotation direction in milliseconds
    previousMillis = currentMillis;

    // toggle rotation direction
    rotationDirection = 1 - rotationDirection;
  }

  // if rotation direction = 1, move stepper motor clockwise
  if (rotationDirection == 1) {
    // print rotation direction
    Serial.println("clockwise");    
    // step in clockwise direction
    myStepper.step(stepsPerRevolution);
  } 
  
  // if rotation direction = 0, move stepper motor counterclockwise
  if (rotationDirection == 0) {
    // print rotation direction
    Serial.println("counterclockwise");
    // step in counterclockwise direction
    myStepper.step(-stepsPerRevolution);
  }

}