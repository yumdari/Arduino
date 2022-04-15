#include <SimpleTimer.h>

long curTimeMs = 0;
int i = 0;
int j = 0;
int t = 50; // interval
int buzz = 9; // set buzzer up to D9
int buzzState = 0;
int timerState = 1;
int ledState = 1;
int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED reset
int SW4 = 2; // LED start&stop
int cnt = 0; //clock check

SimpleTimer timer;

void setup()
{
  timer.setInterval(1000, Buzz_Timer);
  timer.setInterval(5000, Buzz_Stop);
  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(buzz, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), Led_State, RISING);
  curTimeMs = millis();
}

void loop() {
  Timer_Check();
  timer.run();
  Led_Shift();
  Led_Reset();
}

void Led_Shift()
{
  if (ledState == 1) {
    if (curTimeMs + t < millis())
    {
      Key_Input();
      PORTA = 0x10 << i;
      i++;
      curTimeMs = millis() ;
      if (i > 4) {
        PORTA = 0x00;
        Key_Input();
        PORTC = 0x80 >> j;
        j++;
        curTimeMs = millis() ;
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

void Key_Input() {
  if (digitalRead(SW1) == HIGH)
    t += 5;
  if (digitalRead(SW2) == HIGH)
    t -= 5;
  if (t < 10)
    t = 10;
  else if (t > 100)
    t = 100;
}

void Led_Reset() {
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

void Led_State() {
  ledState = !ledState;
}

void Buzz_Timer() {
  buzzState = !buzzState;
  digitalWrite(buzz, buzzState); // periodly buzz
}

void Buzz_Stop() {
  timerState = ! timerState;
}

void Timer_Check() {
  if (timerState == 0) {
    timer.disable(0);
    digitalWrite(buzz, LOW);
  }
  else if (timerState == 1) {
    timer.enable(0);
  }
}
