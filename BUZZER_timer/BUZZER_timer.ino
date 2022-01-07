#include <MsTimer2.h>

int buzzer=10;
int tones=0;

unsigned long preTime = 0;
unsigned long nowTime = 0;
unsigned char buzzState = 0;

void setup() {
  pinMode(buzzer,OUTPUT);
  
}

void loop() {
  nowTime = millis();
  if(nowTime - preTime >=5000)
    preTime = nowTime;
  //buzzState=!buzzState;
  //digitalWrite(buzzer,buzzState);
  tone(buzzer,261);
}
