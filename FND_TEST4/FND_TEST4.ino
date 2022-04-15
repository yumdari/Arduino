#include <SimpleTimer.h>
#include <MsTimer2.h>

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

SimpleTimer timer;

unsigned long curTimeMs = 0;
unsigned long Signal_Count = 0;
int hour = 0, minute = 0, second = 0;

int i = 0;
int j = 0;
int fndState = 0;
int Signal_Fnd = 0;
int Fnd_Time = 0;

int fndPort[8] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP};

//int digit[4] = {FND_D4, FND_D3, FND_D2, FND_D1};

int fndData[10][8] = {
  { 1, 1, 1, 1, 1, 1, 0, 0}, // 0
  { 0, 1, 1, 0, 0, 0, 0, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0}, // 9
};

void setup() {
  DDRL = 0x0F; // 2, 0   0x00 -> 0x02 0b00000000 0b00000010
  DDRB = 0x0F; // 3, 0   0x00 -> 0x03 0b00000000 0b00000011 ^0x03
  Serial.begin(9600);
  for (int i = 0 ; i < 8 ; i++)
  {
    pinMode(fndPort[i], OUTPUT);
  }
  MsTimer2::set(1000, Clocks);
  MsTimer2::start();
  //timer.setInterval(1, Fnd);
  curTimeMs = millis();
}

void loop() {
  int num = 0;
  int t = millis();

  for (int i = 0; i < 7; i++) {
    PORTL = 0x00;
    digitalWrite(fndPort[i], fndData[second % 10][i]);
    for (int i = 0; i < 7; i++) {
      PORTL = 0x02;
      digitalWrite(fndPort[i], fndData[second / 10][i]);
    }
  }
  for (int i = 0; i < 7; i++) {
    PORTB = 0x00;
    digitalWrite(fndPort[i], fndData[second / 60 % 10][i]);
    for (int i = 0; i < 7 ; i++) {
      PORTB = 0x03;
      digitalWrite(fndPort[i], fndData[second / 60 / 10][i]);
    }
  }
}


void Clocks() {
  second++;
  //t1++;
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

  //if (t1 == 10) {
  //t1 = 0;
  //t2++;
  //}
  //if (t2 == 20)
  //t2 = 10;

  Signal_Fnd = Signal_Count;
  //Serial.println(Signal_Count);
  Serial.print(hour);
  Serial.print(" : ");
  Serial.print(minute);
  Serial.print(" : ");
  Serial.print(second);
  Serial.print(" : ");
  Serial.println(Signal_Count);
  Signal_Count = 0;
}// 1 sec clock
