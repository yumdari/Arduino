#include<stdio.h>
int LED = 26;
int i=0;

unsigned long preTime = 0;
unsigned long nowTime = 0;
unsigned char ledState = 0;


void setup() {


pinMode(LED, OUTPUT);
Serial.begin(9600);
  //A4,A5,A6,A7,C7,C6,C5,C4
}

void loop() {
  nowTime = millis();
       Serial.println(nowTime);
  delay(1000);
      nowTime = 0;
            Serial.println(nowTime);
              delay(1000);
       nowTime = millis();
       Serial.println(nowTime);
         delay(1000);
}
