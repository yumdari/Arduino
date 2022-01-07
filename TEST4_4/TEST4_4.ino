#include <MsTimer2.h>

int i;
int buzz = 9; // set buzzer up to D9
int buzzState = 0;

int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED reset
int SW4 = 2; // LED start&stop
int t = 50; // initial delay

unsigned int curTime = 0; // current time
unsigned int preTime = 0; // previous time
unsigned char ledState = 1; // initial value = LED on

void setup() {
  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(buzz, OUTPUT);
  MsTimer2::set(1000, timer);
  MsTimer2::start();
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), LED_State, RISING);
}

void loop() {
  key_input();
  led_shift();
  LED_reset();
}

void key_input() {
  if (t < 10)
    t = 10;
  else if (t > 90)
    t = 90;
  if (digitalRead(SW1) == HIGH)
    t += 10;
  if (digitalRead(SW2) == HIGH)
    t -= 10;
}

void led_shift() {
  curTime = millis();
  if (ledState == 1)
  {
    if (curTime - preTime > t)
    {
      for (i = 0; i < 5; i++)
      {
        PORTA = 0x10 << i;
        delay(t);
      }
      //for (i = 0; i < 5; i++)
      {
        //PORTC = 0x80 >> i;
        //delay(t);
      }   // toggle LED pin
      curTime = preTime;
    }
  }
  else
  {
    PORTA = 0x00;
    PORTC = 0x00;
  }
}

void LED_reset() {
  if (digitalRead(SW3) == HIGH)
  {
    for (i = 1; i < 4; i++)
    {
      PORTA = 0xF0;
      PORTC = 0xF0;
      delay(100);
      PORTA = 0x00;
      PORTC = 0x00;
      delay(100);
    }
    t = 50;
  }
}
//blink LEDs x3 and set interval up 50 ms

void LED_State() {
  ledState = !ledState;
}

void timer() {
  buzzState = !buzzState;
  analogWrite(buzz, buzzState); // periodly buzz
}
