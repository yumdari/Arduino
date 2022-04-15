#include <SimpleTimer.h>

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

SimpleTimer timer;

void setup()
{
  timer.setInterval(1000, BUZZ_TIMER);
  timer.setInterval(5000, BUZZ_STOP);
  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(buzz, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), LED_STATE, RISING);
}

void loop() {
  TIMER_CHECK();
  timer.run();
  LED_SHIFT();
  KEY_INPUT();
  LED_RESET();
}

void LED_SHIFT()
{
  if (ledState == 1) {
    if (time + t < millis())
    {
      PORTA = 0x10 << i;
      i++;
      time = millis() ;
      if (i > 4) {
        PORTA = 0x00;
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
  if (t < 10)
    t = 10;
  else if (t > 90)
    t = 90;
  if (digitalRead(SW1) == HIGH)
    t += 10;
  if (digitalRead(SW2) == HIGH)
    t -= 10;
}

void LED_RESET() {
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

void LED_STATE() {
  ledState = !ledState;
}

void BUZZ_TIMER() {
  buzzState = !buzzState;
  digitalWrite(buzz, buzzState); // periodly buzz
}

void BUZZ_STOP() {
  timerState = ! timerState;
}

void TIMER_CHECK() {
  if (timerState == 0) {
    timer.disable(0);
    digitalWrite(buzz, LOW);
  }
  else if (timerState == 1) {
    timer.enable(0);
  }
}
