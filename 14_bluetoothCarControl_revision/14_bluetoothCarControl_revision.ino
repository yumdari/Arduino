#include <Servo.h>

#define IN1 2
#define IN2 3

Servo myservo;

int servo_val = 90;

void setup() {
  Serial.begin(9600);
  myservo.attach(4);
}

void loop() {
  if (Serial.available() > 0)
  {
    char readData = Serial.read();
    if (readData == 'f' || readData == 'F')
    {
      Serial.println("forward");
      motor_go();
    }
    else if (readData == 'b' || readData == 'B')
    {
      Serial.println("back");
      motor_back();
    }
    else if (readData == 's' || readData == 'S')
    {
      Serial.println("stop");
      motor_stop();
    }
    else if (readData == 'l' || readData == 'L')
    {
      if (servo_val < 120)
      {
        servo_val = servo_val + 15;
        myservo.write(servo_val);  //왼쪽으로
        Serial.println(servo_val);
      }
    }
    else if (readData == 'r' || readData == 'R')
    {
      if (servo_val > 60)
      {
        servo_val = servo_val - 15;
        myservo.write(servo_val);  //왼쪽으로
        Serial.println(servo_val);
      }
    }
  }
}

void motor_go()
{
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
}

void motor_back()
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
}

void motor_stop()
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}
