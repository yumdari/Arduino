#include<stdio.h>
  int LED[]={26,27,28,29,30,31,32,33};
  int SW=34;
  int i=0;
  int count=0;
  int mode=0;
  int key=1;
  
void setup()
{
  for(i=0; i<8; i++)
  {
    pinMode(LED[i],OUTPUT);
  }
  pinMode(SW,INPUT_PULLUP);
}
void loop()
{
    for(i=0;i<8;i++)
    {
        digitalWrite(LED[i],HIGH);
        delay(key*50);
        digitalWrite(LED[i],LOW);
        delay(key*50);
    }
    if(SW==LOW)
      key++;
    if(key==10)
      key=1;
}
 
