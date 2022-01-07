#include <SimpleTimer.h>
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

SimpleTimer timer;

unsigned long curTimeMs = 0;
unsigned long Signal_Count = 0;
int Led_Shift_Interval = 50; // initial interval
int ledState = 1; //initial LED state
int hour = 0, minute = 0, second = 0;

int i = 0;
int j = 0;
int k = 0;
int l = 0;
int t = 0;

int fndPort[12] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP, FND_D1, FND_D2, FND_D3, FND_D4};

int numArray[] = {
  B0111111,  // MSB   --  LSB
  B0000110,
  B1011011,
  B1001111,
  B1100110,
  B1101101,
  B1111101,
  B0000111,
  B1111111,
  B1101111
};

const int segPins[] = {52, 48, 45, 43, 42, 51, 46, 44}; // Segment핀 번호
const int segNum = 2;                              // Segment 개수 (숫자 자리수)
const int vccPins[segNum] = { 50, 53 };            // 10, 11번 핀을 통해 seg#1, seg#2의 전원 인가

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
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);                   // Segment핀 설정
  }
  for (int i = 0; i < segNum; i++) {
    pinMode(vccPins[i], OUTPUT);                   // seg#0, seg#1의 전원인가 핀 설정
  }
  MsTimer2::set(1000, Clocks);
  MsTimer2::start();
  timer.setInterval(1000, Fnd);
  curTimeMs = millis();
}

void loop() {
  int Key;
  Key = Key_Input();
  timer.run();
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

void Fnd() {
  //for (int i = 0; i < 100; i++) {                  // 0~99까지 숫자를 표시
    for (int n = 0; n < 10; n++) {                 // 빠르게 카운트할 경우 모든 LED가 켜져 있는 것처럼 보여
      showNumber(second);                               // 숫자를 구분할 수 없으므로, 빠르게 10번씩 점멸시키면서 표시
    }
  }
//}

void showNumber(int number) {
  if (number == 0) {
    showDigit(number, 0);                         // 0의 경우 (1의 자리수) Segment에만 0을 출력
  }

  else
  {
    for (int j = 0; j < segNum; j++) {            // 10의 자리, 1의 자리 출력을 위해 2번 실행
      if (number > 0) {                           // 출력값이 0보다 큰 경우에만 실행
        showDigit(number % 10, j);                // 1의 자리 숫자(%10)를 seg#0(j=0)에 출력 (if 10의 자리 숫자 = (number % 100) / 10))
        number = number / 10;                     // ※ 숫자를 10으로 나눠 10의 자리 숫자를 1의 자리 숫자로 만듦
      }                                           // if 처음에 주어진 숫자가 한 자리 수였으면,
      //delay(3);                                   //    → 10으로 나눈 후에는 1의 자리값이 0이 되어, 0보다 큰 값이 안되므로 10의 자리 출력하지 않음
    }                                             // if 처음에 주어진 숫자가 두 자리 수였으면
  }                                               //    → 10으로 나눈 후 10의 자리 숫자가 1의 자리 수가 되므로, 10이 자리수를 seg#1(j=1)에 출력
}

void showDigit(int num, int digit) {              // num값과 digit(0→1의 자리수에 표시, 1→10의 자리수에 표시)을 넘겨받아
  int data = numArray[num];                       // num번째 배열값을 digit자리수에 표시할 data로 지정

  digitalWrite(vccPins[0], HIGH);                 // vcc핀에 전원 인가
  digitalWrite(vccPins[1], HIGH);                 // [0] = Arduino Pin10, [1] = Arduino Pin11

  for (int segLED = 0; segLED < 7; segLED++)      // 숫자 2진수의 7세그먼트 ON, OFF
  {
    if (data & 0x01) {                            // 1이면
      digitalWrite(segPins[segLED], HIGH);        // HIGH(끄고)
    }
    else {                                        // 1이 아니면(0이면)
      digitalWrite(segPins[segLED], LOW);         // LOW(끈다)
    }
    data >>= 1;                                   // data값을 1비트씩 오른쪽으로 쉬프트한 후
  }
  digitalWrite(vccPins[digit], LOW);              // 숫자 LED 한 자리 ON
}
