#include<Servo.h>

#define IN1 2
#define IN2 3
#define TRIG_PIN 12
#define ECHO_PIN 13

Servo myservo;

int servo_val = 90;

void setup() {
  Serial.begin(9600);
  myservo.attach(4);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, OUTPUT);
  myservo.write(90);
  motor_go();
}

void loop() {
  if (ultrasonic_cm(TRIG_PIN, ECHO_PIN) < 30)
  {
    motor_stop();
    delay(1000);
    motor_back();
    delay(1000);
    myservo.write(60); // move to right
    motor_go();
    delay(500);
    myservo.write(90); // move to senter
    motor_go();
  }
}

void motor_go()
{
  analogWrite(IN1, 85);  
  analogWrite(IN2, 0);
}

void motor_back()
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 85);
}

void motor_stop()
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}

int ultrasonic_cm(char trig, char echo)
{
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  return ((float)(340 * duration) / 10000) / 2;
}
