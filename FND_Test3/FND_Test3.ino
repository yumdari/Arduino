#include <SimpleTimer.h>
#include <MsTimer2.h>

int hour = 0, minute = 0, second = 0;
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

int fndState = 0;
int t1 = 0;
int t2 = 10;
int curTimeMs = 0;

int fndPort[12] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP, FND_D1, FND_D2, FND_D3, FND_D4};

int fndData[20][12] = {
  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, // 0 - d1
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

  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1}, // 00 - d10
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 10
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1}, // 20
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1}, // 30
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1}, // 40
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 50
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 60
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1}, // 70
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 80
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 90
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 20 - Blank
};

void setup() {
  Serial.begin(9600);
  for (int i = 0 ; i < 21 ; i++)
  {
    pinMode(fndPort[i], OUTPUT);
  }

  MsTimer2::set(1000, Clocks);
  MsTimer2::start();
  timer.setInterval(10, Fnd);
  curTimeMs = millis();
}

void Clocks()
{
  second++;
  t1++;
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
  Serial.println(second);
  //Serial.print(hour);
  //Serial.print(" : ");
  //Serial.print(minute);
  //Serial.print(" : ");
  //Serial.println(second);
}// 1 sec clock

void loop() {
  timer.run();
}

void Fnd() {
  if (t1 == 10) {
    t1 = 0;
    t2++;
  }
  if (t2 == 20)
    t2 = 10;
  fndState = ! fndState ;
  if (fndState == 1) {
    if (second > 10) {
      for (int i = 0 ; i < 12 ; i++)
        digitalWrite(fndPort[i], fndData[t2][i]);
    }
  }
  else if (fndState == 0) {
    for (int j = 0; j < 12; j++)
      digitalWrite(fndPort[j], fndData[t1][j]);
  }
}
