#include <ESP32Servo.h>

Servo myServo;  // create servo object to control a servo

      // variable to store the servo position

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 27;
int pos = 0;
unsigned long curTimeMs = 0;

void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
   myServo.setPeriodHertz(50);    // standard 50 hz servo
   myServo.attach(servoPin, 500, 2500); // attaches the servo on pin 25 & 32 to the servo object
  // using default min/max of 1000us and 2000us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  Serial.begin(9600);
  curTimeMs = millis();
}

void loop() {
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//     myServo.write(pos);    // tell servo to go to position in variable 'pos'
//    delay(5);             // waits 5ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myServo.write(pos);    // tell servo to go to position in variable 'pos'
//    delay(5);             // waits 5ms for the servo to reach the position
if(curTimeMs + 10 < millis()){
        myServo.write(pos);
        pos++;
        if(pos >180)
        pos = 0;
        Serial.println(pos);
       curTimeMs = millis();
  }
}
