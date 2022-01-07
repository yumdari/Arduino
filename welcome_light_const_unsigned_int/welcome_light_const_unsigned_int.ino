#include<stdio.h>
  int LED[] = {26};

void setup()
{

  pinMode(LED26,OUTPUT);
  pinMode(SW1,INPUT_PULLUP);
}
void loop()
{
    digitalWrite(LED26,HIGH);
  
}
