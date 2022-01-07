#include<stdio.h>

long time = millis() ;
int i = 0;
int j = 0;
int t = 100; // interval
int buzz = 7; // set buzzer up to D9
int buzzState = 0;
int timerState = 1;
int ledState = 1;
int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED reset
int SW4 = 2; // LED start&stop

void setup() {
  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
}

void loop() {

  LED_SHIFT();
}

void LED_SHIFT()
{
  if (ledState == 1) {
    if (time + t < millis())
    {
      KEY_INPUT();
      PORTA = 0x10 << i;
      i++;
      time = millis() ;
      if (i > 4) {
        PORTA = 0x00;
        KEY_INPUT();
        PORTC = 0x80 >> j;
        j++;
        time = millis() ;
        if ( j > 4)
        {
          i = 0;
          j = 0;
        }
      }
    }
  }
  else {
    PORTA = 0x00;
    PORTC = 0x00;
  }
}

void KEY_INPUT() {
  if (digitalRead(SW1) == HIGH)
    t += 10;
  if (digitalRead(SW2) == HIGH)
    t -= 10;
  if (t < 10)
    t = 10;
  else if (t > 100)
    t = 100;
}
