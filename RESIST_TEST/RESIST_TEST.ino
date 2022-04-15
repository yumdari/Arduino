#include <MsTimer2.h>

int i = 0;
int buzz = 9; // set buzzer up to D9
int buzzState = 1;
int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED start&stop
int SW4 = 37; // LED reset
int t = 50; // initial delay

void setup() {
  DDRA = 0xF0;
  DDRC = 0xF0;
  Serial.begin(9600);
  //A4,A5,A6,A7,C7,C6,C5,C4
  pinMode(SW1, INPUT);
}

void loop() {
  led_shift();
}

void led_shift() {
  if(digitalRead(SW1) == HIGH)
      PORTA = 0x10;
      else
        PORTA = 0x00;
      Serial.println(digitalRead(SW1));
 
 
}
