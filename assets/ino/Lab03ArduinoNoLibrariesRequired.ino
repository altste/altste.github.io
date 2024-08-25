// Arduino_lab_3_no_libraries.ino
// CSC 230 Fall 2023
// Arduino Lab #3 Ultrasonic Sensor - Without Libraries
//
// Author: Steve Ellermann
// Modified: 2023-02-28
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

#define TRIG_PIN 12     // for the ultrasonic sensor
#define ECHO_PIN 11     // for the ultrasonic sensor
#define BUZZER_PIN 8    // for passive buzzer
#define NOTE_C5  523    // for passive buzzer
#define NOTE_G5  784    // for passive buzzer
long duration;
long distance;

void setup() {
   Serial.begin(9600);
   // initialize digital pin TRIG_PIN as an output.
   pinMode(TRIG_PIN, OUTPUT);
   // initialize digital pin ECHO_PIN as an input.
   pinMode(ECHO_PIN, INPUT);
   // initialize digital pin LED_BUILTIN as an output.
   pinMode(LED_BUILTIN, OUTPUT);
   // initialize digital pin BUZZER_PIN as an output.
   pinMode(BUZZER_PIN, OUTPUT);
}

// repeat infinitely 
void loop() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
   
    distance = (duration * 0.0343) / 2;
 
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


