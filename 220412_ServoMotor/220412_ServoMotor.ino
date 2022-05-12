#include <Servo.h>
Servo myservo;

void setup() {
  myservo.attach(9);
  pinMode(A0, INPUT);
}

void loop() {
  int analogIn = analogRead(A0);
  int val = map(analogIn, 0, 1023, 0, 180);
  myservo.write(val);
}
