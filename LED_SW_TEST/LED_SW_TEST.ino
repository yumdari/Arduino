#include<stdio.h>

 int SW=34;
 int LED=23;

 void setup() {
  pinMode(SW,INPUT);
  pinMode(SW,INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

 void loop() {
  if(digitalRead(SW)==HIGH)
  {
    digitalWrite(LED,HIGH);
    Serial.println(HIGH);
    Serial.println(1);
  }
    else
    digitalWrite(LED,HIGH);
    Serial.println(LOW);
}
