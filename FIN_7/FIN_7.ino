#include <MsTimer2.h>

#define SW_DOWN 34
#define SW_UP 35
#define SW_RESTART 36
#define SW_TOGGLE 38
#define BUZZER 6 // 6 : BLUE LED, 9 : BUZZER
#define GEN_SIGNAL 5
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RESTART 3
#define KEY_TOGGLE 4

unsigned long curTimeMs = 0;
unsigned long Signal_Count = 0;
int Led_Shift_Interval = 1000; // initial interval
int ledState = 1; //initial LED state
int hour = 0, minute = 0, second = 0;

int i = 0;
int j = 0;

void setup()
{
  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(BUZZER, OUTPUT);
  pinMode(SW_DOWN, INPUT);
  pinMode(SW_UP, INPUT);
  pinMode(SW_RESTART, INPUT);
  pinMode(SW_TOGGLE, INPUT);
  pinMode(GEN_SIGNAL, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), Count_Clock, RISING);
  Serial.begin(9600);
  MsTimer2::set(1000, Clocks);
  MsTimer2::start();
  curTimeMs = millis();

}

void loop() {
  int Key;
  Key = Key_Input();
  switch (Key) {
    case KEY_DOWN : // LED Speed Down
      Led_Shift_Interval += 5;
      //if (Led_Shift_Interval > 100)
      //Led_Shift_Interval = 100;
      break;

    case KEY_UP : // LED Speed Up
      Led_Shift_Interval -= 5;
      //if (Led_Shift_Interval < 10)
      //Led_Shift_Interval = 10;
      break;

    case KEY_RESTART : // LED Restart
      Led_Restart();
      break;

    case KEY_TOGGLE : // LED Toggle
      ledState = ! ledState;
      break;
  }
  //Serial.println(Signal_Count);
  Led_Shift();
  Buzz_Timer();
  Clock_Signal();
}

int Key_Input() {
  int Key_In = 0;
  if (digitalRead(SW_DOWN) == HIGH)
    Key_In = KEY_DOWN;
  if (digitalRead(SW_UP) == HIGH)
    Key_In = KEY_UP;
  if (digitalRead(SW_RESTART) == HIGH)
    Key_In = KEY_RESTART;
  if (digitalRead(SW_TOGGLE) == HIGH)
    Key_In = KEY_TOGGLE;
  return Key_In;
}

void Led_Shift()
{
  if (ledState == 1) {
    if (curTimeMs + Led_Shift_Interval < millis())
    {
      PORTA = 0x10 << i;
      i++;
      curTimeMs = millis() ;
      if (i > 4) {
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
    else if (ledState == 0) {
      PORTA = 0x00;
      PORTC = 0x00;
    }
  }
}

void Led_Restart()
{
  int i = 0;
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

void Buzz_Timer()
{
  if (second % 10 == 0) {
    digitalWrite(BUZZER, HIGH); // periodly BUZZER
  }
  Buzz_Stop();
}

void Buzz_Stop()
{
  if (second % 10 == 1) {
    digitalWrite(BUZZER, LOW);
  }
}

void Clocks()
{
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
  Serial.println(Signal_Count);
  Signal_Count = 0;
  //Serial.print(hour);
  //Serial.print(" : ");
  //Serial.print(minute);
  //Serial.print(" : ");
  //Serial.println(second);
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
