#include <MsTimer2.h>
#define SW_UP 34
#define SW_DOWN 35
#define SW_RESTART 36
#define SW_Led_Toggle 38
#define BUZZER 6 // 6 : BLUE LED, 9 : BUZZER
#define GEN_SIGNAL 5

unsigned long curTimeMs = 0;
unsigned long Signal_Count = 0;
int Led_Shift_Interval = 50; // initial interval
int ledState = 1; //initial LED state
int hour = 0, minute = 0, second = 0;

//int i = 0;
//int j = 0;

void setup()
{
  MsTimer2::set(1000, clocks);
  MsTimer2::start();

  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(BUZZER, OUTPUT);
  pinMode(SW_DOWN, INPUT);
  pinMode(SW_UP, INPUT);
  pinMode(SW_RESTART, INPUT);
  pinMode(SW_Led_Toggle, INPUT);
  pinMode(GEN_SIGNAL, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), Count_Clock, RISING);
  Serial.begin(9600);
  curTimeMs = millis();
}

void loop() {
  int Key;
  switch (Key) {
    case 1 :
      Led_Shift_Interval += 5;
    case 2 :
      Led_Shift_Interval -= 5;
    case 3 :

    case 4 :

  }
  Buzz_Timer();
  Led_Shift(int Led_Speed);
  LED_RESTART();
}

void Led_Shift()
{
  if (curTimeMs + Led_Shift_Interval < millis())
  {
    Led_Toggle();
    Key_Input();
    PORTA = 0x10 << i;
    Clock_Signal();
    Led_Toggle();
    i++;
    curTimeMs = millis() ;
    if (i > 4) {
      PORTA = 0x00;
      Key_Input();
      PORTC = 0x80 >> j;
      Clock_Signal();
      Led_Toggle();
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

void Key_Input() {
  int Key_In = 0;
  if (digitalRead(SW_DOWN) == HIGH)
    Led_Shift_Interval += 5;
  if (digitalRead(SW_UP) == HIGH)
    Led_Shift_Interval -= 5;
  if (Led_Shift_Interval < 10)
    Led_Shift_Interval = 10;
  else if (Led_Shift_Interval > 100)
    Led_Shift_Interval = 100;
}

void () {
  if (digitalRead(SW_RESTART) == HIGH)
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
    Led_Shift_Interval = 50;
  }
}
//blink LEDs x3 and set interval up 50 ms

void Led_Toggle() {
  if (digitalRead(SW_Led_Toggle) == HIGH) {
    ledState = !ledState;
  }
  if (ledState == 0) {
    PORTA = 0x00;
    PORTC = 0x00;
  }
}

void Buzz_Timer() {
  if (second % 10 == 0) {
    digitalWrite(BUZZER, HIGH); // periodly BUZZER
  }
  Buzz_Stop();
}

void Buzz_Stop() {
  if (second % 10 == 1) {
    digitalWrite(BUZZER, LOW);
  }
}

void clocks() {
  second++;
  if (second == 60)
  {
    second = 0;
    minute++;
  }
  if (minute == 60)
  {
    minute = 0;
    hour++;
  }
  Serial.print(hour);
  Serial.print(" : ");
  Serial.print(minute);
  Serial.print(" : ");
  Serial.print(second);
  Serial.print(" ::: ");
  Serial.println(Signal_Count);
}// 1 sec clock

void Clock_Signal() {
  if (PORTA == 0x10 || PORTA == 0x40 || PORTC == 0x80 || PORTC == 0x20) {
    digitalWrite(GEN_SIGNAL, HIGH);
  }
  else {
    digitalWrite(GEN_SIGNAL, LOW);
  }
}

void Count_Clock() {
  Signal_Count++;
}
