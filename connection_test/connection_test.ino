#include<stdio.h>

int SW = 2;
int LED = 26;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

}
void loop() {
  if (digitalRead(SW) == HIGH)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);

}
