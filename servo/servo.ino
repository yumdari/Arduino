#include <Servo.h>
Servo myservo;

int i=90;


void setup()
{
  myservo.attach(4); 
}

void loop()
{
  myservo.write(60);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(120);
  delay(1000);
  
}
