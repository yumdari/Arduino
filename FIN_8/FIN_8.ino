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

#define FND_A 52
#define FND_B 48
#define FND_C 45
#define FND_D 43
#define FND_E 42
#define FND_F 51
#define FND_G 46
#define FND_DP 44
#define FND_D1 53
#define FND_D2 50
#define FND_D3 49
#define FND_D4 47

unsigned long curTimeMs = 0;
unsigned long Signal_Count = 0;
int Led_Shift_Interval = 50; // initial interval
int ledState = 1; //initial LED state
int hour = 0, minute = 0, second = 0;

int i = 0;
int j = 0;
int k = 0;
int l = 0;

int fndPort[12] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP, FND_D1, FND_D2, FND_D3, FND_D4};

int fndData[40][12] = {
  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, // 0 - 1
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, // 10 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1}, // 0 - 2
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 10 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1}, // 0 - 3
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1}, // 10 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1}, // 0 - 4
  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 10 - Blank
};

void setup() {
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
  for (int i = 0 ; i < 41 ; i++)
  {
    pinMode(fndPort[i], OUTPUT);
  }
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
  Fnd();
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

void Fnd() {
  for (int k = 0 ; k < 40 ; k++) {
    for (int l = 0 ; l < 12 ; l++) {
      digitalWrite(fndPort[l], fndData[k][l]);
    }
  }
}
