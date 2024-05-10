// Lab02ArduinoServo.ino
//
// Modified by: Steve Ellermann
// Modified date:  2023-03-01
// 
// Original code by: www.elegoo.com
// Original date: 2016-12-18
//
// Library Required: Servo.zip
// https://github.com/arduino-libraries/Servo

#include <Servo.h>

Servo myservo;                             // create servo object to control a servo
                                           // twelve servo objects can be created on most boards

int pos = 0;                               // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9);                       // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {    // goes from 0 degrees to 180 degrees
                                           // in steps of 1 degree
    myservo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(5);                              // waits 15ms for the servo to reach the position
  }
  
  delay(1000);                             // wait 1 second
  
  for (pos = 180; pos >= 0; pos -= 1) {    // goes from 180 degrees to 0 degrees
    myservo.write(pos);                    // tell servo to go to position in variable 'pos'
    delay(5);                              // waits 15ms for the servo to reach the position
  }
  
  delay(1000);                             // wait 1 second
  
}