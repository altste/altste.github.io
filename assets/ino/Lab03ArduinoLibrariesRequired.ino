// Arduino_lab_3_libraries_required.ino
// 
// Author: Steve Ellermannn
// Modified: 2023-02-28
//
// Library required: HC-SR04.zip
// Library required: pitches.zip
//
// https://www.arduino.cc/reference/en/
//
// Ardunio (Elegoo) Uno R3 Board
// 5V Passive Buzzer
// HC-SR04 Ultrasonic Module
//
// Passive Bussier Wiring
// + to Digital "8"
// - to Digital "GND"
//
// HC-SR04 Ultrasonic Module Wiring
// VCC to Power "5V"
// TRIG to Digital "12"
// ECHO to Ditial "11"
// GND to Power "GND" 

// Library for Ultrasonic Sennsor
#include "SR04.h"
// Library for Passive Buzzer
#include "pitches.h"

// For the ultrasonic sensor
#define TRIG_PIN 12
#define ECHO_PIN 11

// For the passive buzzer
#define BUZZER_PIN 8

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

long distance;

void setup() {
   Serial.begin(9600);
}

// repeat infinitely 
void loop() {
   distance=sr04.Distance();
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println(" cm");
   delay(100);

   if (distance > 5) {
     // turn the LED on (HIGH is the voltage level)
     digitalWrite(LED_BUILTIN, HIGH);

     // play a tone on the passive buzzer
     tone(8, NOTE_C5, 100);
     
     // wait for 100 milliseconds
     delay(100);
     
     // turn the LED off by making the voltage LOW                      
     digitalWrite(LED_BUILTIN, LOW);

     // turn the tone off
     noTone(8);
    
    // wait for 1000 milliseconds
	  delay(1000);
   }

  if (distance <= 5) {
     // turn the LED on (HIGH is the voltage level)
     digitalWrite(LED_BUILTIN, HIGH);

     // play a tone on the passive buzzer
     tone(8, NOTE_G5, 100);
     
     // wait for 100 milliseconds
     delay(100);
     
     // turn the LED off by making the voltage LOW                      
     digitalWrite(LED_BUILTIN, LOW);

     // turn the tone off
     noTone(8);
    
    // wait for 100 milliseconds
	  delay(100);
  }
}