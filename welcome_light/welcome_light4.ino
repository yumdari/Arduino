#include<stdio.h>
int i;
void setup()
{
  pinMode(8,OUTPUT);
    pinMode(7,OUTPUT);
      pinMode(6,OUTPUT);
}
void loop()
{   
    for(i=0;i<255;i++)
    {
    analogWrite(7,i);
    delay(5);
    }
    for(i=255;i>0;i--)
    {
    analogWrite(7,i);
    delay(5);
    }

}
