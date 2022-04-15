#include <MsTimer2.h>

int buzzer=10;

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
  digitalWrite(buzzer,261);
}
